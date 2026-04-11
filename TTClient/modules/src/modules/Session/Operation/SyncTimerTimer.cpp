
#include "stdafx.h"
#include <modules/ITcpClientModule.h>
#include <modules/Session/Operation/SyncTimerTimer.h>
#include <network/imcore.h>
#include <protocol/IM.Message.pb.h>

SyncTimeTimer::SyncTimeTimer() : m_timeCount(0), m_serverTime(0) {
  m_serverTime = (UInt32)time(0);
}

void SyncTimeTimer::process() {
  ++m_serverTime;
  ++m_timeCount;
  if (m_timeCount >= 600) {
    m_timeCount = 0;
    network::IMLibCoreStartOperationWithLambda([]() {
      IM::Message::IMClientTimeReq imClientTimeReq;
      module::getTcpClientModule()->sendPacket(
        IM::BaseDefine::ServiceID::SID_MSG, IM::BaseDefine::MessageCmdID::CID_MSG_TIME_REQUEST, &imClientTimeReq);
    });
  }
}

void SyncTimeTimer::release() {
  delete this;
}
