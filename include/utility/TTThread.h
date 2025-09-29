
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:Windows线程处理的封装
*/

#ifndef TTTHREAD_27D478B1_0BAD_4015_A6E5_8AF2DA7739BF_H__
#define TTTHREAD_27D478B1_0BAD_4015_A6E5_8AF2DA7739BF_H__

#include "GlobalDefine.h"
#include "utility/utility_dll.h"

NAMESPACE_BEGIN(util)

class UTILITY_CLASS TTThread
{
public:
    TTThread();
    ~TTThread();
public:
	BOOL create();
	void destory();
	BOOL wait(DWORD dwWaitTime);
	inline DWORD getThreadId() { return m_dwThreadID; }
protected:
	virtual UInt32 process();

private:
	static UInt32 __stdcall _threadProc(void *lpParam);

private:
	HANDLE		m_hThread;
	DWORD		m_dwThreadID;
};

NAMESPACE_END(util)

#endif// TTTHREAD_27D478B1_0BAD_4015_A6E5_8AF2DA7739BF_H__
