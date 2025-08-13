/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef TCPSOCKETSMANAGER_2EAF3E98_E9C6_4F3D_ADE6_387E54BCA3AC_H__
#define TCPSOCKETSMANAGER_2EAF3E98_E9C6_4F3D_ADE6_387E54BCA3AC_H__

#include "network/imconn.h"

class TcpSocketsManager
{
public:
    ~TcpSocketsManager();
	static TcpSocketsManager* getInstance();

public:
	net_handle_t connect(const char* server_ip, uint16_t server_port);
	CImConn* get_client_conn(uint32_t nHandle);
	void release_by_handle(net_handle_t handle);
	void unRegisterCallback(net_handle_t handle);
	void registerCallback(net_handle_t handle,ITcpSocketCallback* pCB);

private:
	TcpSocketsManager();

private:
	ConnMap_t		m_client_conn_map;
};

#endif// TCPSOCKETSMANAGER_2EAF3E98_E9C6_4F3D_ADE6_387E54BCA3AC_H__
