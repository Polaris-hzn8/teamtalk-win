
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef ISESSIONMODULE_070C0321_0708_4487_8028_C1D8934B709D_H__
#define ISESSIONMODULE_070C0321_0708_4487_8028_C1D8934B709D_H__

#include <global_define.h>
#include <modules/Base/ICallbackOpertaion.h>
#include <modules/Base/ModuleBase.h>
#include <modules/module_dll.h>

namespace DuiLib {
class CControlUI;
class CPaintManagerUI;
}  // namespace DuiLib
class MessageEntity;
NAMESPACE_BEGIN(module)
const std::string MODULE_SESSION_PREFIX = "session";

// KEYID
const std::string KEY_SESSION_NEWMESSAGE =
  MODULE_SESSION_PREFIX + "NewMessage";  // 收到新消息（包含离线消息、离线消息推送）
const std::string KEY_SESSION_OPENNEWSESSION = MODULE_SESSION_PREFIX + "OpenNewSession";   // 通知打开一个会话
const std::string KEY_SESSION_SENDMSG_TOOFAST = MODULE_SESSION_PREFIX + "SendMsgTooFast";  // 发送消息太快
const std::string KEY_SESSION_SENDMSG_FAILED = MODULE_SESSION_PREFIX + "SendMsgFialed";    // 发送消息失败
const std::string KEY_SESSION_SHAKEWINDOW_MSG = MODULE_SESSION_PREFIX + "ShakeWindowMsg";  // 窗口抖动消息
const std::string KEY_SESSION_WRITING_MSG = MODULE_SESSION_PREFIX + "WritingMsg";          // 正在输入
const std::string KEY_SESSION_STOPWRITING_MSG = MODULE_SESSION_PREFIX + "StopWrtingMsg";   // 停止正在输入状态
const std::string KEY_SESSION_SENDMSGTIP_KEY = MODULE_SESSION_PREFIX + "SendMsgTipKey";    // 发送消息快捷键
const std::string KEY_SESSION_TRAY_STARTEMOT = MODULE_SESSION_PREFIX + "TrayStartEmot";    // 托盘图标闪烁
const std::string KEY_SESSION_TRAY_STOPEMOT = MODULE_SESSION_PREFIX + "TrayStopEmot";      // 关闭托盘图标闪烁
const std::string KEY_SESSION_TRAY_NEWMSGSEND =
  MODULE_SESSION_PREFIX + "TrayNewMsgSend";                                            // 发送一条新消息到托盘的提示框
const std::string KEY_SESSION_TRAY_COPYDATA = MODULE_SESSION_PREFIX + "TrayCopyData";  // 托盘模块发现新消息通知
const std::string KEY_SESSION_HISTORY_MESSAGE = MODULE_SESSION_PREFIX + "HistoryMessage";  // 收到历史消息
const std::string KEY_SESSION_MESSGEREADED_NOTIFY =
  MODULE_SESSION_PREFIX + "MessageReadEdNotify";  // 有人阅读了发出去的消息
const std::string KEY_SESSION_UPDATE_RECENTLY_SESSIONLIST =
  MODULE_SESSION_PREFIX + "UpdateRecentlySessionList";  // 更新最近会话列表
const std::string KEY_SESSION_UPDATE_TOTAL_UNREADMSG_COUNT =
  MODULE_SESSION_PREFIX + "UpdateTotalUnReadMsgCount";  // 更新未读消息数

enum {
  SESSION_ERRORTYPE = 0,
  SESSION_USERTYPE,   // 用户会话
  SESSION_GROUPTYPE,  // 群会话
};
class SessionEntity {
 public:
  SessionEntity();
  std::string getAvatarPath();
  UInt8 getOnlineState();
  CString getName();
  void setUpdatedTimeByServerTime();
  std::string getOriginSessionId();
  UInt32 getOriginIntegerSessionId();

 public:
  UInt8 sessionType;      // SESSION_USERTYPE / SESSION_GROUPTYPE
  UInt32 updatedTime;     // 信息更新的时间
  std::string sessionID;  // 会话ID
  UInt32 latestmsgId = 0;
  std::string latestMsgContent;  // 最后一条消息内容
  std::string latestMsgFromId;   // 最后一条消息的发送者ID
  UInt8 sessionStatus;           // 是否删除
};

typedef std::map<std::string, SessionEntity> SessionEntityMap;
class MODULE_API ISessionModule : public module::ModuleBase, public module::IPduPacketParse {
 public:
  virtual DuiLib::CControlUI* createMainDialogControl(LPCTSTR pstrClass, DuiLib::CPaintManagerUI& paintManager) = 0;

  // 用户模块初始化，用于初始化加载用户数据
  virtual BOOL startup() = 0;

  // 同步服务器时间
  virtual UInt32 getTime() const = 0;
  virtual void setTime(IN UInt32 time) = 0;
  virtual void startSyncTimeTimer() = 0;

  // SessionEntityManager委托包装
  virtual void setSessionEntity(IN const module::SessionEntity& sessionInfo) = 0;         // 更新会话信息（用于创建）
  virtual void getRecentSessionList(OUT std::vector<std::string>& vecRecentSession) = 0;  // 获取最近用于展示的会话列表
  virtual BOOL getSessionEntityBySId(IN const std::string& sId, OUT module::SessionEntity& sessionEntity) = 0;
  virtual void updateSessionEntityByMsg(IN const MessageEntity& msg) = 0;
  virtual void deleteSessionEntity(IN const std::string& sessionId) = 0;
  virtual UInt32 getGlobalUpdateTime()
    const = 0;  // 从服务器端获取最近更新的会话列表，需要提交给服务器一次更新会话的时间
  virtual void setGlobalUpdateTime(IN const UInt32 updateTime) const = 0;
};

MODULE_API ISessionModule* getSessionModule();

NAMESPACE_END(module)

#endif  // ISESSIONMODULE_070C0321_0708_4487_8028_C1D8934B709D_H__
