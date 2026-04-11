
#ifndef SESSIONMODULE_IMPL_414A6CFB_C817_43C4_9C73_7E965E7317C7_H__
#define SESSIONMODULE_IMPL_414A6CFB_C817_43C4_9C73_7E965E7317C7_H__

#include <modules/ISessionModule.h>

class SyncTimeTimer;
class MessageEntity;
class SessionModule_Impl final : public module::ISessionModule {
 public:
  SessionModule_Impl();
  virtual ~SessionModule_Impl() = default;
  virtual void onPacket(network::TTPBHeader& header, std::string& pbBody);

 public:
  virtual DuiLib::CControlUI* createMainDialogControl(IN LPCTSTR pstrClass, IN DuiLib::CPaintManagerUI& paintManager);

  virtual BOOL startup();

  virtual UInt32 getTime() const;
  virtual void setTime(UInt32 time);
  virtual void startSyncTimeTimer();

  virtual void setSessionEntity(IN const module::SessionEntity& sessionInfo);
  virtual void getRecentSessionList(OUT std::vector<std::string>& vecRecentSession);
  virtual BOOL getSessionEntityBySId(IN const std::string& sId, OUT module::SessionEntity& sessionEntity);
  virtual void updateSessionEntityByMsg(IN const MessageEntity& msg);
  virtual void deleteSessionEntity(IN const std::string& sessionId);
  virtual UInt32 getGlobalUpdateTime() const;
  virtual void setGlobalUpdateTime(IN const UInt32 updateTime) const;

 private:
  // 消息过滤器
  void _sessionMsgData(IN std::string& pbBody);
  void _sessionMsgACK(IN const UInt16 seqNo, IN std::string& pbBody);
  void _sessionMsgTimeResponse(IN std::string& pbBody);
  void _sessionMsgUnreadCntResponse(IN std::string& pbBody);
  void _sessionMsgReadNotify(IN std::string& pbBody);
  void _sessionUnReadMsgListResponse(IN std::string& pbBody);
  void _sessionHistoryMsgListResponse(IN UInt16 reserved, IN std::string& pbBody);

  BOOL _checkMsgFromStranger(IN MessageEntity& msg);  // 检查消息发送者ID是否在当前会话ID列表中，不存在则要去获取
  BOOL _banGroupMSG(IN MessageEntity msg);            // 群消息屏蔽
  BOOL _prase2LocalMsg(OUT MessageEntity& msg);       // 解析成本地可展示的消息
 private:
  SyncTimeTimer* m_pSyncTimer;
};

#endif  // SESSIONMODULE_IMPL_414A6CFB_C817_43C4_9C73_7E965E7317C7_H__
