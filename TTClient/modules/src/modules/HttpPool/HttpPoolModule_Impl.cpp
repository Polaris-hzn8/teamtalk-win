
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: HTTP连接池模块
*/

#include <modules/HttpPool/HttpPoolModule_Impl.h>

namespace module
{
	module::IHttpPoolModule* getHttpPoolModule()
	{
		static HttpPoolModule_Impl module;
		return &module;
	}
}

///////////////////////////////////////////////////////////////////////////////
// HttpPoolModule_Impl
///////////////////////////////////////////////////////////////////////////////
HttpPoolModule_Impl::HttpPoolModule_Impl()
	:m_hSemaphore(NULL)
	, m_bShutdown(FALSE)
	, m_maxThreadCount(1)
{
	m_vecHttpThread.reserve(m_maxThreadCount);
	m_hSemaphore = ::CreateSemaphore(NULL, 0, LONG_MAX, NULL);
	if (!m_hSemaphore)
	{
		LOG__(ERR, _T("HttpPoolModule_Impl: CreateSemaphore failed"));
	}
}

HttpPoolModule_Impl::~HttpPoolModule_Impl()
{
	shutdown();
	if (m_hSemaphore)
	{
		CloseHandle(m_hSemaphore);
		m_hSemaphore = NULL;
	}
}

void HttpPoolModule_Impl::pushHttpOperation(module::IHttpOperation* pOperaion, BOOL bHighPriority /*= FALSE*/)
{
	if (NULL == pOperaion)
		return;

	CAutoLock lock(&m_mtxLock);
	if (m_bShutdown)
	{
		LOG__(ERR, _T("HttpPoolModule_Impl::pushHttpOperation called after shutdown; releasing op"));
		try
		{
			pOperaion->release();
		}
		catch (...)
		{
			LOG__(ERR, _T("pushHttpOperation: release exception"));
		}
		return;
	}
	
	if (bHighPriority)
	{
		m_lstHttpOpers.push_front(pOperaion);
	}
	else
	{
		m_lstHttpOpers.push_back(pOperaion);
	}

	_launchThread();

	if (m_hSemaphore)
	{
		ReleaseSemaphore(m_hSemaphore, 1, NULL);//获取结果
	}
	return;
}

void HttpPoolModule_Impl::shutdown()
{
	_cancelAllOperations();

	//获取结果
	for (TTHttpThread* pThread : m_vecHttpThread)
	{
		if (pThread)
		{
			pThread->requestExit();
		}
	}

	for (size_t i = 0; i < m_vecHttpThread.size(); ++i)
	{
		if (m_hSemaphore)
		{
			ReleaseSemaphore(m_hSemaphore, 1, NULL);
		}
	}

	for (TTHttpThread* pThread : m_vecHttpThread)
	{
		if (pThread)
		{
			if (!pThread->waitForExit(2000))
			{
				LOG__(ERR, _T("HttpPoolModule_Impl::shutdown: thread did not exit in 2000ms (id: %lu)"), pThread->getThreadId());
			}
			delete pThread;
			pThread = NULL;
		}
	}

	m_vecHttpThread.clear();
}

BOOL HttpPoolModule_Impl::_launchThread()
{
	CAutoLock lock(&m_mtxLock);

	if ((int)m_vecHttpThread.size() >= m_maxThreadCount)
	{
		return TRUE;
	}

	TTHttpThread* pThread = new TTHttpThread(this);
	if (!pThread)
	{
		LOG__(ERR, _T("_launchThread: new TTHttpThread failed"));
		return FALSE;
	}

	if (!pThread->create())
	{
		LOG__(ERR, _T("_launchThread: thread create failed"));
		delete pThread;
		return FALSE;
	}

	m_vecHttpThread.push_back(pThread);
	return TRUE;
}

void HttpPoolModule_Impl::_cancelAllOperations()
{
	CAutoLock lock(&m_mtxLock);

	for (module::IHttpOperation* pOper : m_lstHttpOpers)
	{
		try
		{
			pOper->release();
		}
		catch (...)
		{
			LOG__(ERR, _T("cancel operation unknown exception"));
		}
	}
	m_lstHttpOpers.clear();
}

///////////////////////////////////////////////////////////////////////////////
// TTHttpThread
///////////////////////////////////////////////////////////////////////////////
TTHttpThread::TTHttpThread(HttpPoolModule_Impl* owner)
	:m_Owner(owner)
	,m_bContinue(TRUE)
{

}

TTHttpThread::~TTHttpThread()
{

}

UInt32 TTHttpThread::process()
{
	if (!m_Owner)
		return 0;

	module::IHttpOperation* pHttpOper = NULL;
	HttpPoolModule_Impl* pPool = m_Owner;
	while (m_bContinue)
	{
		DWORD dwResult = WaitForSingleObject(pPool->m_hSemaphore, INFINITE);
		if (WAIT_OBJECT_0 != dwResult)
			break;

		if (!m_bContinue)
			break;

		{
			CAutoLock lock(&(pPool->m_mtxLock));
			if (!pPool->m_lstHttpOpers.empty())
			{
				pHttpOper = pPool->m_lstHttpOpers.front();
				pPool->m_lstHttpOpers.pop_front();
			}
			else
			{
				pHttpOper = NULL;
			}
		}

		if (!m_bContinue)
			break;

		try
		{
			if (pHttpOper)
			{
				pHttpOper->process();
				pHttpOper->release();
			}
		}
		catch (...)
		{
			LOG__(ERR, _T("TTHttpThread: Failed to execute opertaion(0x%p)"), pHttpOper);
		}
	}

	return 0;
}
