
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: im cross platform library,currently include network��opertion manager
*/

#ifndef _IMCORE_H_
#define _IMCORE_H_

#include <iostream>
#include <string.h>
#include <functional>

#include "util.h"
#include "GlobalDefine.h"

class ClientConn;
struct ITcpSocketCallback;

NAMESPACE_BEGIN(imcore)

const std::string OPERATION_NAME_MSG_READ_ACK = "operation_name_msg_read_ack";

class Operation;

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
	unsigned int __stdcall event_run(void* threadArgu);
#else
	void* event_run(void* arg);
#endif

// start/stop
NETWORK_DLL bool IMLibCoreRunEvent();
NETWORK_DLL bool IMLibCoreStopEvent();
NETWORK_DLL bool IMLibCoreIsRunning();

// network
NETWORK_DLL int IMLibCoreConnect(std::string ip, int port);
NETWORK_DLL int IMLibCoreWrite(int key, uchar_t* data, uint32_t size);
NETWORK_DLL void IMLibCoreShutdown(int key);
NETWORK_DLL void IMLibCoreClose(int key);
NETWORK_DLL void IMLibCoreRegisterCallback(int handle,ITcpSocketCallback* pCB);
NETWORK_DLL void IMLibCoreUnRegisterCallback(int handle);

// operation
// ������в���
NETWORK_DLL void IMLibCoreStartOperation(IN Operation* pOperation, Int32 delay = 0);

// ������в���Lambda
NETWORK_DLL void IMLibCoreStartOperationWithLambda(std::function<void()> operationRun
    , Int32 delay = 0
    , std::string oper_name = "_common_operation_name");

// �������ɾ��
NETWORK_DLL void IMLibCoreClearOperationByName(std::string oper_name);

#ifdef __cplusplus
}
#endif

NAMESPACE_END(imcore)

#endif// _IMCORE_H_

