
 /*
  Reviser: Polaris_hzn8
  Email: lch2022fox@163.com
  Github: https://github.com/Polaris-hzn8
  brief: Windows线程处理的封装
 */

#include "stdafx.h"
#include "utility/TTThread.h"

NAMESPACE_BEGIN(util)

TTThread::TTThread()
:m_hThread(0)
{

}

TTThread::~TTThread()
{
	if (m_hThread)
		::CloseHandle(m_hThread);
	m_hThread = 0;
}

BOOL TTThread::create()
{
	m_hThread = (HANDLE)_beginthreadex(0,0, _threadProc, this, 0, (unsigned*)&m_dwThreadID);

	if (m_hThread < (HANDLE)2)
	{
		m_hThread = 0;
		m_dwThreadID = 0;
	}

	return m_hThread >(HANDLE)1;
}

void TTThread::destory()
{
	if (m_hThread)
	{
		::TerminateThread(m_hThread, 0);
		WaitForSingleObject(m_hThread, 500);
		::CloseHandle(m_hThread);
		m_hThread = 0;
		m_dwThreadID = 0;
	}
}

BOOL TTThread::wait(DWORD dwWaitTime)
{
	if (m_hThread == 0)
		return TRUE;
	return (::WaitForSingleObject(m_hThread, dwWaitTime) != WAIT_TIMEOUT);
}

UInt32 TTThread::process()
{
	return 0;
}

UInt32 __stdcall TTThread::_threadProc(void *lpParam)
{
	TTThread* pThread = (TTThread*)lpParam;
	assert(pThread);
	if (pThread != 0)
	{
		pThread->process();
	}
	return 0;
}

NAMESPACE_END(util)
