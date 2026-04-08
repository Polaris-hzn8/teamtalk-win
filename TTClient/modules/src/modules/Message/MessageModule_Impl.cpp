
#include "stdafx.h"
#include <modules/Message/MessageModule_Impl.h>
#include <modules/Message/ReceiveMsgManage.h>
#include <modules/Message/SendMsgManage.h>

#include <modules/IDatabaseModule.h>
#include <modules/IMiscModule.h>
#include <modules/ISessionModule.h>
#include <modules/ISysConfigModule.h>
#include <modules/ITcpClientModule.h>
#include <network/ImCore.h>
#include <network/core/ImPduBase.h>
#include <protocol/IM.Message.pb.h>
#include <utility/utilStrCodingAPI.h>

namespace module {
IMessageModule* getMessageModule() {
  static MessageModule_Impl module;
  return &module;
}
}  // namespace module

MessageModule_Impl::MessageModule_Impl() {}

MessageModule_Impl::~MessageModule_Impl() {}

void MessageModule_Impl::removeMessageBySId(const std::string& sId) {
  ReceiveMsgManage::getInstance()->removeMessageBySId(sId);
}

BOOL MessageModule_Impl::pushMessageBySId(const std::string& sId, MessageEntity& msg) {
  return ReceiveMsgManage::getInstance()->pushMessageBySId(sId, msg);
}

BOOL MessageModule_Impl::getHistoryMessage(IN const std::string& sId,
                                           IN UInt32 nMsgCount,
                                           IN BOOL scrollBottom,
                                           OUT std::vector<MessageEntity>& msgList) {
  // step 0 get message id from cache
  module::SessionEntity sessEntity;
  if (!module::getSessionModule()->getSessionEntityBySId(sId, sessEntity)) {
    LOGA__(ERR, "getSessionEntityBySId failed,sessionId:%s", util::stringToCString(sId));
    return FALSE;
  }
  UInt32 topMsgId = _getSessionTopMsgId(sId);
  if (0 == topMsgId) {
    topMsgId = sessEntity.latestmsgId;
  }

  // step 1 query history message from local db
  std::vector<MessageEntity> msgListTemp;
  module::getDatabaseModule()->sqlGetHistoryMessage(sId, topMsgId, nMsgCount, msgListTemp);

  // step 2 compare the topMsgId to latest local db msgId and check which is sequential
  if (!msgListTemp.empty()) {
    // todo 校验消息ID是否连续,检查msgCount+1与实际消息数是否一致
    MessageEntity& latestMsgEntity = msgListTemp.front();
    MessageEntity& firstMsgEntity = msgListTemp.back();
    if ((topMsgId == latestMsgEntity.msgId) && ((firstMsgEntity.msgId + nMsgCount - 1) == latestMsgEntity.msgId)) {
      msgList = msgListTemp;
      setSessionTopMsgId(sId, firstMsgEntity.msgId - 1);
      return TRUE;
    }
  }

  // final fetch history message from server db
  imcore::IMLibCoreStartOperationWithLambda([=]() mutable {
    LOG__(APP,
          _T("IMGetMsgListReq history message ,sessionId = %s,sessionName=%s,last msgId = %d,Count = %d"),
          util::stringToCString(sessEntity.sessionID),
          sessEntity.getName(),
          topMsgId,
          nMsgCount);
    IM::Message::IMGetMsgListReq imGetMsgListReq;
    imGetMsgListReq.set_user_id(module::getSysConfigModule()->userId());
    imGetMsgListReq.set_session_type((IM::BaseDefine::SessionType)sessEntity.sessionType);
    imGetMsgListReq.set_session_id(sessEntity.getOriginIntegerSessionId());
    imGetMsgListReq.set_msg_id_begin(topMsgId);  // 比较群成员排序
    imGetMsgListReq.set_msg_cnt(nMsgCount);

    UInt16 reserved = (TRUE == scrollBottom) ? imcore::RESERVED_TYPE_HISTORY_SCROLLBOTTOM_MESSAGE
                                             : imcore::RESERVED_TYPE_HISTORY_MESSAGE;
    module::getTcpClientModule()->sendPacket(
      IM::BaseDefine::SID_MSG, IM::BaseDefine::CID_MSG_LIST_REQUEST, reserved, &imGetMsgListReq);
  });
  return FALSE;
}

void MessageModule_Impl::setSessionTopMsgId(const std::string& sId, UInt32 msgId) {
  std::lock_guard<std::mutex> lock(m_lock);
  m_mapSessionTopMsgId[sId] = msgId;
}

UInt32 MessageModule_Impl::_getSessionTopMsgId(const std::string& sId) {
  std::lock_guard<std::mutex> lock(m_lock);
  auto iterMsgId = m_mapSessionTopMsgId.find(sId);
  UInt32 topMsgId = 0;
  if (iterMsgId != m_mapSessionTopMsgId.end()) {
    topMsgId = iterMsgId->second;
  }

  return topMsgId;
}

void MessageModule_Impl::removeAllMessage() {
  ReceiveMsgManage::getInstance()->removeAllMessage();
}

UInt32 MessageModule_Impl::getTotalUnReadMsgCount(void) {
  return ReceiveMsgManage::getInstance()->getTotalUnReadMsgCount();
}
