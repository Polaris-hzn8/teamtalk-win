
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: http operation thread pool
*/

#ifndef HTTPPOOLMODULE_IMPL_43FDB575_36B4_4CFC_B205_89A9D1904A4C_H__
#define HTTPPOOLMODULE_IMPL_43FDB575_36B4_4CFC_B205_89A9D1904A4C_H__

#include "Modules/IHttpPoolModule.h"
#include "utility/TTThread.h"
#include "network/Lock.h"
#include <vector>
#include <list>

using namespace util;
class TTHttpThread;

class HttpPoolModule_Impl final : public module::IHttpPoolModule
{
	friend class TTHttpThread;
public:
	HttpPoolModule_Impl();
    virtual ~HttpPoolModule_Impl();
public:
	virtual void    pushHttpOperation(module::IHttpOperation* pOperaion, BOOL bHighPriority = FALSE);
	virtual void    shutdown();
private:
	/* 加载线程 */
	virtual BOOL  _launchThread();
	/* 取消所有任务 */
	virtual void  _cancelAllOperations();
private:
	CLock									m_mtxLock;
	std::list<module::IHttpOperation*>		m_lstHttpOpers;
	std::vector<TTHttpThread*>				m_vecHttpThread;
	HANDLE									m_hSemaphore;
};

class TTHttpThread : public util::TTThread
{
	friend class HttpPoolModule_Impl;
public:
	TTHttpThread();
	void shutdown();
private:
	virtual UInt32 process();
private:
	BOOL            m_bContinue;
};

#endif// HTTPPOOLMODULE_IMPL_43fdb575-36b4-4cfc-b205-89a9d1904a4c_H__
