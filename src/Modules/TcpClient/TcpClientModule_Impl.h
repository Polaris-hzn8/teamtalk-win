
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 客户端TCP网络长连接模块实现
*/

#ifndef TCPCLIENTMODULE_IMPL_7C021D09_7902_44DE_BE96_F22561B99198_H__
#define TCPCLIENTMODULE_IMPL_7C021D09_7902_44DE_BE96_F22561B99198_H__

#include "network/imconn.h"
#include "network/TTPBHeader.h"
#include "Modules/ITcpClientModule.h"

class TcpClientModule_Impl;
using namespace module;

// 模块器端的心跳的维护
class ServerPingTimer : public module::ITimerEvent
{
public:
	ServerPingTimer(TcpClientModule_Impl* pTcpClient);
	virtual void process();
	virtual void release();

public:
	BOOL									m_bHasReceivedPing;
	TcpClientModule_Impl*					m_pTcpClient;
};

// 客户端TCP网络长连接模块实现
// 对TcpClientScoket做一个适配
class TcpClientModule_Impl final :
	public ITcpClientModule,
	public ITcpSocketCallback
{
	friend class ServerPingTimer;
public:
	TcpClientModule_Impl();
    virtual ~TcpClientModule_Impl();
public:
	virtual IM::Login::IMLoginRes* doLogin(CString &linkaddr, UInt16 port
		, CString& uName, std::string& pass);
	virtual void shutdown();
	virtual void sendPacket(UInt16 moduleId, google::protobuf::MessageLite* pbBody);
	virtual void sendPacket(UInt16 moduleId, UInt16 cmdId, google::protobuf::MessageLite* pbBody);
	virtual void sendPacket(UInt16 moduleId, UInt16 cmdId, UInt16 seq,google::protobuf::MessageLite* pbBody);

	virtual void startHeartbeat();
	virtual UInt8 getTcpClientNetState()const;

public:
	virtual void onReceiveData(const char* data, int32_t size);
	virtual void onReceiveError();
	virtual void onConnectDone();
	virtual void onClose();

private:
	void _stopHearbeat();
	void _handlePacketOperation(const char* data, UInt32 size);
	void _startServerPingTimer();
	void _stopServerPingTimer();
	void _doReloginServer();
	void _sendPacket(google::protobuf::MessageLite* pbBody);

private:
	IM::Login::IMLoginRes*			m_pImLoginResp;
	module::ITimerEvent*			m_pHearbeatTimer;
	ServerPingTimer*				m_pServerPingTimer;
	BOOL							m_bDoReloginServerNow;
	UInt8							m_tcpClientState;
	HANDLE							m_eventConnected;
	HANDLE							m_eventReceived;
	int								m_socketHandle;
	imcore::TTPBHeader				m_TTPBHeader;
};

#endif// TCPCLIENTMODULE_IMPL_7c021d09-7902-44de-be96-f22561b99198_H__
