
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 自定义封装的lock_guard
*/

#ifndef __LOCK_H__
#define __LOCK_H__

#include "network/ostype.h"
#include "network/networkdll.h"

class NETWORK_DLL CFastLock
{
public:
	CFastLock();
	~CFastLock();
public:
#ifdef _MSC_VER
	CRITICAL_SECTION m_critical_section;
#else
	pthread_mutex_t m_mutex;
#endif
};

class NETWORK_DLL CLock
{
public:
    void lock();
    void unlock();
#ifndef _MSC_VER
    virtual bool try_lock();
#endif
private:
	CFastLock	m_lock;
};

class NETWORK_DLL CAutoLock
{
public:
    CAutoLock(CLock* pLock);
    virtual ~CAutoLock();
private:
    CLock* m_pLock;
};

#endif
