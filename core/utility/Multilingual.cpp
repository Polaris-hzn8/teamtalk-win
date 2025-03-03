
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#include "stdafx.h"
#include "GlobalConfig.h"
#include "utility/utilCommonAPI.h"
#include "utility/Multilingual.h"

NAMESPACE_BEGIN(util)

Multilingual::Multilingual()
{

}

Multilingual::~Multilingual()
{

}

CString Multilingual::getStringById(LPCTSTR strID)
{
	CString cfgPath = util::getParentAppPath() + UTIL_MULTILIGNUAL;
	TCHAR szValue[MAX_PATH];
	::GetPrivateProfileString(_T("DEFAULT"),strID,_T(""), szValue, MAX_PATH, cfgPath);
	return szValue;
}

Multilingual* getMultilingual()
{
	static Multilingual multi;
	return &multi;
}

NAMESPACE_END(util)

