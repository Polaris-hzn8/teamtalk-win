
#include "stdafx.h"
#include <modules/IDatabaseModule.h>
#include <modules/IMessageModule.h>
#include <modules/IMiscModule.h>
#include <modules/ISessionModule.h>
#include <modules/ISysConfigModule.h>
#include <modules/ITcpClientModule.h>
#include <modules/Message/SendMsgManage.h>
#include <imcore/extra/ImCore.h>
#include <imcore/impdu/im_pdu_base.h>
#include <protocol/IM.Message.pb.h>
#include <utility/utilStrCodingAPI.h>

namespace {
const UInt8 TIMEOUT_SENDINGMSG = 5;   // 正在发送的消息，超时为5S
const UInt8 SENDMSG_RETRY_CNT = 1;    //
const UInt32 SENDMSG_INTERVAL = 100;  // 时间间隔为100毫秒
}  // namespace

SendMsgManage::SendMsgManage() {
  CheckSendMsgTimer* pCheckSendMsgTimer = new CheckSendMsgTimer(this);
  module::getEventManager()->scheduleTimer(pCheckSendMsgTimer, 1, TRUE);
  srand(static_cast<UInt32>(time(0)));
}

SendMsgManage::~SendMsgManage() {}

void SendMsgManage::pushSendingMsg(IN MessageEntity& msg) {
  SendingMsg sendingMsg;
  std::lock_guard<std::mutex> lock(m_lock);
  if (m_ListSendingMsg.empty()) {
    sendingMsg.sendtime = static_cast<long>(clock());
    sendingMsg.msg = msg;
    sendingMsg.seqNo = _getSeqNo();
    sendingMsg.status = MSGSTATUS_SENDING;
    m_ListSendingMsg.push_back(sendingMsg);
    sendMessage(sendingMsg);
  } else {
    sendingMsg.sendtime = static_cast<long>(clock());
    sendingMsg.msg = msg;
    sendingMsg.seqNo = _getSeqNo();
    SendingMsg& BackMsg = m_ListSendingMsg.back();
    if (sendingMsg.sendtime - BackMsg.sendtime > SENDMSG_INTERVAL) {
      m_ListSendingMsg.push_back(sendingMsg);
      SendingMsgList::iterator itBegin = m_ListSendingMsg.begin();

      if (itBegin->status == MSGSTATUS_TOSEND) {
        itBegin->status = MSGSTATUS_SENDING;
        sendMessage(*itBegin);
      }
    } else {  // 发送频率太快
      module::getSessionModule()->asynNotifyObserver(module::KEY_SESSION_SENDMSG_TOOFAST,
                                                     sendingMsg.msg.sessionId);  // 发送消息太快
      return;
    }
  }
}
void SendMsgManage::getSendFailedMsgs(OUT SendingMsgList& FailedMsgList) {
  std::lock_guard<std::mutex> lock(m_lock);
  if (m_ListSendingMsg.empty()) {
    return;
  }
  SendingMsg& itFront = m_ListSendingMsg.front();
  if (itFront.waitSeconds > TIMEOUT_SENDINGMSG && itFront.retrySendCnt <= SENDMSG_RETRY_CNT) {
    std::copy(m_ListSendingMsg.begin(), m_ListSendingMsg.end(), std::back_inserter(FailedMsgList));
  }
  m_ListSendingMsg.clear();
}

SendMsgManage* SendMsgManage::getInstance() {
  static SendMsgManage manager;
  return &manager;
}

UInt32 SendMsgManage::_getSeqNo(void) {
  static UInt16 seqNo = static_cast<UInt16>(rand() % 1000);
  if (seqNo > (imcore::TTPBHEADER_RESERVED_MASK - 1)) {
    seqNo = static_cast<UInt16>(rand() % 1000);
  }
  return ++seqNo;
}

BOOL SendMsgManage::popUpSendingMsgByAck(IN const UInt16 seqNo, IN const UInt32 msgID) {
  std::lock_guard<std::mutex> lock(m_lock);
  // 找到对应的seqNo的缓存的项，erase掉
  SendingMsgList::iterator iter = m_ListSendingMsg.begin();
  for (; iter != m_ListSendingMsg.end(); ++iter) {
    if (iter->seqNo == seqNo) {
      // 将消息保存到DB
      iter->msg.msgId = msgID;
      module::getDatabaseModule()->sqlInsertMessage(iter->msg);
      // 更新会话到内存和DB
      module::getSessionModule()->updateSessionEntityByMsg(iter->msg);

      SendingMsgList::iterator iterNext = m_ListSendingMsg.erase(iter);
      if (iterNext != m_ListSendingMsg.end() && iterNext->status == MSGSTATUS_TOSEND)  // 发下一个
      {
        iterNext->status = MSGSTATUS_SENDING;
        sendMessage(*iterNext);
      }

      return TRUE;
    }
  }
  return FALSE;
}

void SendMsgManage::clearSendMessageList() {
  if (!m_ListSendingMsg.empty()) {
    m_ListSendingMsg.clear();
  }
}

void SendMsgManage::sendMessage(IN SendingMsg& sendingMsg) {
  imcore::IMLibCoreStartOperationWithLambda([=]() mutable {
    IM::Message::IMMsgData imMsgData;
    imMsgData.set_from_user_id(module::getSysConfigModule()->userId());
    std::string sToId = sendingMsg.msg.getOriginSessionId();
    imMsgData.set_to_session_id(util::stringToInt32(sToId));
    imMsgData.set_msg_id(0);  // 发送的时候没有消息id，传0即可
    imMsgData.set_create_time(sendingMsg.msg.msgTime);
    imMsgData.set_msg_type(static_cast<IM::BaseDefine::MsgType>(sendingMsg.msg.msgType));
    imMsgData.set_msg_data(sendingMsg.msg.content);
    module::getTcpClientModule()->sendPacket(
      IM::BaseDefine::ServiceID::SID_MSG, IM::BaseDefine::MessageCmdID::CID_MSG_DATA, sendingMsg.seqNo, &imMsgData);
  });
}

//////////////////////////////////////////////////////////////////////////
CheckSendMsgTimer::CheckSendMsgTimer(SendMsgManage* pMsgCheck) : m_pMsgCheck(pMsgCheck) {}

CheckSendMsgTimer::~CheckSendMsgTimer() {}

void CheckSendMsgTimer::process() {
  if (m_pMsgCheck == nullptr) {
    return;
  }

  std::lock_guard<std::mutex> lock(m_pMsgCheck->m_lock);
  if (m_pMsgCheck->m_ListSendingMsg.empty()) {
    return;
  }
  SendingMsg& itFront = m_pMsgCheck->m_ListSendingMsg.front();
  if (itFront.status == MSGSTATUS_SENDING)  // 队首为正在发送的消息
  {
    ++itFront.waitSeconds;
    if (itFront.waitSeconds > TIMEOUT_SENDINGMSG)  // 超时处理
    {
      if (itFront.retrySendCnt < SENDMSG_RETRY_CNT) {
        ++itFront.retrySendCnt;
        itFront.waitSeconds = 0;
        // 消息发送失败一次后，重试一次
        m_pMsgCheck->sendMessage(itFront);
      } else  // 若队列中首个消息发送失败，则认为整个消息队列都超时
      {
        module::getSessionModule()->asynNotifyObserver(module::KEY_SESSION_SENDMSG_FAILED,
                                                       itFront.msg.sessionId);  // 发送消息失败
      }
    }
  } else if (MSGSTATUS_TOSEND == itFront.status)  // 队首为等待发送状态的消息
  {
    itFront.status = MSGSTATUS_SENDING;
    m_pMsgCheck->sendMessage(itFront);
  }
}

void CheckSendMsgTimer::release() {
  delete this;
}