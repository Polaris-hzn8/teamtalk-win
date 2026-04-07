 
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 发送消息时的有关管理
*/

#ifndef SENDMSGMANAGE_5545E32E_5320_4A45_ABD0_5AC0F09EE7AF_H__
#define SENDMSGMANAGE_5545E32E_5320_4A45_ABD0_5AC0F09EE7AF_H__

#include <list>
#include <network/basic/lock.h>
#include <modules/Base/IEvent.h>
#include <modules/Base/ITimerEvent.h>
#include <modules/MessageEntity.h>

enum MSG_SENDSTATUS
{
	MSGSTATUS_TOSEND,
	MSGSTATUS_SENDING,
};
struct SendingMsg
{
	SendingMsg()
	:retrySendCnt(0)
	, waitSeconds(0)
	, seqNo(0)
	, sendtime(0)
	, status(MSGSTATUS_TOSEND)
	{

	}
	MSG_SENDSTATUS		status;
	long				sendtime;		//发送的投递中的时间，聊天消息的网络延迟和发消息频率
	UInt8               retrySendCnt;	//重试次数
	UInt8               waitSeconds;	//等待重试的时间
	UInt16              seqNo;			//
	MessageEntity		msg;			//
};
typedef std::list<SendingMsg>  SendingMsgList;

// 发送消息时队列有关管理
class SendMsgManage
{
	friend class CheckSendMsgTimer;
public:
    SendMsgManage();
    ~SendMsgManage();
public:
	void pushSendingMsg(IN MessageEntity& msg);
	BOOL popUpSendingMsgByAck(IN const UInt16 seqNo,IN const UInt32 msgID);
	void getSendFailedMsgs(OUT SendingMsgList& FailedMsgList);
	void clearSendMessageList();
	static SendMsgManage* getInstance();

	void sendMessage(IN  SendingMsg& msg);
private:
	UInt32 _getSeqNo(void);
	
private:
	SendingMsgList				m_ListSendingMsg;
	CLock			m_lock;
};

// 定时check消息管理器，是否超时
class CheckSendMsgTimer : public module::ITimerEvent
{
public:
	CheckSendMsgTimer(SendMsgManage* pMsgCheck);
	virtual ~CheckSendMsgTimer();
	virtual void process();
	virtual void release();

private:
	SendMsgManage*      m_pMsgCheck;
};

#endif// SENDMSGMANAGE_5545E32E_5320_4A45_ABD0_5AC0F09EE7AF_H__
