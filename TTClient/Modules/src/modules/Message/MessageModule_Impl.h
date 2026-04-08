
#ifndef HISTORYMSGMODULE_IMPL_C28C3F8C_9A47_48DF_840B_BE394EAFFFEA_H__
#define HISTORYMSGMODULE_IMPL_C28C3F8C_9A47_48DF_840B_BE394EAFFFEA_H__

#include <map>
#include <modules/IMessageModule.h>
#include <network/basic/lock.h>

class CppSQLite3DB;
class MessageModule_Impl final : public module::IMessageModule {
 public:
  MessageModule_Impl();
  virtual ~MessageModule_Impl();

 public:
  virtual BOOL getHistoryMessage(IN const std::string& sId,
                                 IN UInt32 nMsgCount,
                                 IN BOOL scrollBottom,
                                 OUT std::vector<MessageEntity>& msgList);
  virtual void setSessionTopMsgId(const std::string& sId, UInt32 msgId);

  virtual void removeMessageBySId(const std::string& sId);  // 当删除相关用户或者群需要删除消息
  virtual void removeAllMessage();
  virtual BOOL pushMessageBySId(const std::string& sId, MessageEntity& msg);
  virtual UInt32 getTotalUnReadMsgCount(void);

 private:
  void _closeDB();
  void _msgToTrace(const MessageEntity& msg);
  UInt32 _getSessionTopMsgId(const std::string& sId);

 private:
  CLock m_lock;
  std::map<std::string, UInt32> m_mapSessionTopMsgId;  // 会话顶部最新一条显示信息的msg_id
};

#endif  // HISTORYMSGMODULE_IMPL_C28C3F8C_9A47_48DF_840B_BE394EAFFFEA_H__
