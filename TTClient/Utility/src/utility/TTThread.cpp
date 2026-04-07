
 /*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: Windows线程处理的封装
 */

#include "stdafx.h"
#include <utility/TTThread.h>

NAMESPACE_BEGIN(util)

TTThread::TTThread():
	m_hThread(NULL),
	m_dwThreadID(0)
{

}

TTThread::~TTThread()
{
	if (m_hThread)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

BOOL TTThread::create()
{
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, _threadProc, this, 0, (unsigned*)&m_dwThreadID);
	if (m_hThread == NULL)
	{
		m_dwThreadID = 0;
		return FALSE;
	}
	return TRUE;
}

void TTThread::destory()
{
	if (m_hThread)
	{
		TerminateThread(m_hThread, 0);
		WaitForSingleObject(m_hThread, 500);
		CloseHandle(m_hThread);
		m_hThread = NULL;
		m_dwThreadID = 0;
	}
}

BOOL TTThread::wait(DWORD dwWaitTime)
{
	if (m_hThread == NULL)
		return TRUE;
	DWORD dwResult = WaitForSingleObject(m_hThread, dwWaitTime);
	return (dwResult != WAIT_TIMEOUT);
}

// 重写处理逻辑
UInt32 TTThread::process()
{
	return 0;
}

UInt32 __stdcall TTThread::_threadProc(void *lpParam)
{
	TTThread* pThread = (TTThread*)lpParam;
	assert(pThread);
	if (pThread != NULL)
	{
		pThread->process();
	}
	return 0;
}

NAMESPACE_END(util)
