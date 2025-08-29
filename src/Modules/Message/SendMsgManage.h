 
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: ����Ϣʱ����й���
*/

#ifndef SENDMSGMANAGE_5545E32E_5320_4A45_ABD0_5AC0F09EE7AF_H__
#define SENDMSGMANAGE_5545E32E_5320_4A45_ABD0_5AC0F09EE7AF_H__

#include <list>
#include "network/Lock.h"
#include "Modules/IEvent.h"
#include "Modules/ITimerEvent.h"
#include "Modules/MessageEntity.h"

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
	long				sendtime;		//�����Ͷ��е�ʱ�䣬������Ϣ��ļ������̫С�����Ʒ���ϢƵ��
	UInt8               retrySendCnt;	//���Դ���
	UInt8               waitSeconds;	//�����д��ڵ�ʱ��
	UInt16              seqNo;			//
	MessageEntity		msg;			//
};
typedef std::list<SendingMsg>  SendingMsgList;

// ����Ϣʱ����й���
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

// ��ʱcheck��Ϣ�����Ƿ�ʱ
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
