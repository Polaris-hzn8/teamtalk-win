
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#include "stdafx.h"
#include "Modules/ModuleObserver.h"
#include "Modules/ModuleSubject.h"
#include <vector>
#include <algorithm>

NAMESPACE_BEGIN(module)

MKOEvent_Impl::MKOEvent_Impl(IN ModuleSubject* p)
: m_pMko(p)
, m_mkoInt(0)
, m_pmkoVoid(nullptr)
{

}

MKOEvent_Impl::~MKOEvent_Impl()
{
}

void MKOEvent_Impl::process()
{
	if (nullptr == m_pMko)
	{
		return;
	}
	std::vector<MKODelegate> lstMKOCallbacks;
	m_pMko->getIObserverHandlersByModuleId(lstMKOCallbacks);
	if (lstMKOCallbacks.empty())
		return;

	for (MKODelegate callback : lstMKOCallbacks)
	{
		try
		{
			callback(m_keyId, std::make_tuple(m_mkoString, m_mkoInt, m_pmkoShardVoid, m_pmkoVoid));
		}
		catch (const std::bad_function_call&)
		{
			LOG__(ERR, _T("bad function call-m_keyId:%d"), m_keyId);
		}
		catch (...)
		{
			LOG__(ERR, _T("unknown exception"));
		}

	}
}

void MKOEvent_Impl::release()
{
	delete this;
}

ModuleObserverCtx::ModuleObserverCtx(MKODelegate& hd, void* pObserObject)
	: callback(hd)
	, m_pObserverObject(pObserObject)
{

}

NAMESPACE_END(module)
