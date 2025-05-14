
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#include "stdafx.h"
#include "DialogManager.h"
#include <algorithm>

NAMESPACE_BEGIN(DuiLib)

DialogManager::DialogManager()
{

}

DialogManager::~DialogManager()
{
}

DialogManager* DialogManager::getInstance()
{
	static DialogManager manager;
	return &manager;
}

void DialogManager::registerDialog(WindowImplBase* pDialog)
{
	auto iterDialog = std::find_if(m_vecDialogs.begin(), m_vecDialogs.end(),
		[=](WindowImplBase* pD)
	{
		return (pD == pDialog);
	});
	if (iterDialog != m_vecDialogs.end())
		return;

	m_vecDialogs.push_back(pDialog);
}

void DialogManager::unRegisterDialog(WindowImplBase* pDialog)
{
	auto iterDialog = std::remove_if(m_vecDialogs.begin(), m_vecDialogs.end(),
		[=](WindowImplBase* pD)
	{
		return (pDialog == pD);
	});
	if (iterDialog != m_vecDialogs.end())
	{
		m_vecDialogs.erase(iterDialog, m_vecDialogs.end());
	}
}

void DialogManager::closeAllDialogs()
{
	for (WindowImplBase* pDialog : m_vecDialogs)
	{
		pDialog->Close();
	}
	m_vecDialogs.clear();
}

NAMESPACE_END(DuiLib)
