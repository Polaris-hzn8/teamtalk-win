
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 接收消息时的有关管理
*/

#ifndef RECEIVEMSGMANAGE_B3CDCA98_9B4E_482C_8342_7F2DF985F6D3_H__
#define RECEIVEMSGMANAGE_B3CDCA98_9B4E_482C_8342_7F2DF985F6D3_H__

#include <list>
#include <map>
#include <modules/Base/IEvent.h>
#include <modules/MessageEntity.h>
#include <mutex>

typedef std::list<MessageEntity> SessionMessage_List;
typedef std::map<std::string, SessionMessage_List> SessionMessageMap;

class ReceiveMsgManage {
 public:
  virtual ~ReceiveMsgManage();
  static ReceiveMsgManage* getInstance();

 private:
  ReceiveMsgManage();

 public:
  BOOL pushMessageBySId(const std::string& sId, MessageEntity& msg);
  BOOL popMessageBySId(const std::string& sId, MessageEntity& msg);
  /**
   * 取最新的一个消息，但不是pop,主要用于推送消息预览和给联系人发消息
   *
   * @param   const std::string & sId
   * @param   MessageEntity & msg
   * @return  BOOL
   * @exception there is no any exception to throw.
   */
  BOOL frontMessageBySId(const std::string& sId, MessageEntity& msg);
  BOOL popMessagesBySId(IN const std::string& sId,
                        OUT SessionMessage_List& msgList,
                        IN MSG_TYPE_STATUS status = MESSAGE_TYPE_NONE,
                        IN const UINT32 msgId = 0);
  UInt32 getUnReadMsgCountBySId(const std::string& sId);
  UInt32 getTotalUnReadMsgCount();
  void removeAllMessage();
  /**
   * 清除接口目前不是很高级，这个操作在对方收到该消息时使用，不适用于服务收到返回该消息
   *
   * @param   const std::string & sId
   * @return  void
   * @exception there is no any exception to throw.
   */
  void removeMessageBySId(const std::string& sId);
  void parseContent(CString& content, BOOL bFloatForm, Int32 chatWidth);  // 该函数处理的过滤
 private:
  SessionMessage_List* _getChatMsgListBySID(const std::string& sId);
  void _Quickchat2Fromat(OUT CString& content);  // 转换 @小七 字符
  void _urlReplace(CString& content);
  void _urlScan(CString& content);
  void _replaceUrlParts(CString& content);

 private:
  SessionMessageMap m_mapSessionMsg;
  std::mutex m_lock;
  std::vector<CString> m_scanUrls;

 public:
  /**
   * 消息去重
   *
   * @param   IN const MessageEntity & msg
   * @param   IN const UInt32 seqNo
   * @return  BOOL
   * @exception there is no any exception to throw.
   */
  BOOL checkIsReduplicatedMsg(IN const MessageEntity& msg, IN const UInt32 seqNo);

 private:
  struct ReceiveMsg {
    MessageEntity msg;
    UInt32 seqNo;
  };
  typedef std::list<ReceiveMsg> ReceiveMsgList;
  typedef std::map<std::string, ReceiveMsgList> ReceiveMsgMap;

  ReceiveMsgMap m_MsgMap;
  // 消息去重//end
};

//////////////////////////////////////////////////////////////////////////
class AudioMessageMananger  // 音频消息
{
 public:
  ~AudioMessageMananger();
  static AudioMessageMananger* getInstance();

  BOOL playAudioMsgByAudioSid(IN const std::string& sSessionID, IN const std::string& sAID);
  BOOL autoplayNextUnReadAudioMsg();

  BOOL audioProcess();
  BOOL makeAppAudioSid(IN const UInt32 msgId, IN const std::string sSessionId, OUT std::string& sAID);
  BOOL saveAudioDataToFile(IN UCHAR* data, IN UINT32 lenth, IN std::string sFileName);
  BOOL getAudioMsgLenth(IN UCHAR* data, IN UINT32 lenth, OUT UInt8& AudioMsgLen);

  BOOL pushAudioMessageBySId(const std::string& sId, MessageEntity& msg);
  BOOL popPlayingAudioMsg();
  BOOL clearAudioMsgBySessionID(IN const std::string sSessionID);
  BOOL stopPlayingAnimate();

 private:
  BOOL startPlayingAnimate(IN const std::string& sToPlayAID);

  SessionMessageMap m_mapUnReadAudioMsg;

  std::string m_sPlayingSessionID;  // 当前正在播放的会话ID
  std::string m_sPlayingAID;        // 当前正在播放或正在播放动画的AID
};

#endif  // RECEIVEMSGMANAGE_B3CDCA98_9B4E_482C_8342_7F2DF985F6D3_H__
