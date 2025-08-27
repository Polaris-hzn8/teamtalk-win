
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: ini工具类封装
*/

#ifndef _INI_OPERATION_H_
#define _INI_OPERATION_H_

#include "GlobalDefine.h"
#include "utility/utilityDll.h"
#include <windows.h>

NAMESPACE_BEGIN(util)

class UTILITY_CLASS CIniReader
{
public:
	CIniReader(LPCTSTR szFileName);
	~CIniReader() = default;
	int ReadInteger(LPCTSTR szSection, LPCTSTR szKey, int iDefaultValue);
	float ReadFloat(LPCTSTR szSection, LPCTSTR szKey, float fltDefaultValue);
	bool ReadBoolean(LPCTSTR szSection, LPCTSTR szKey, bool bolDefaultValue);
	CString ReadString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefaultValue);
private:
	TCHAR m_szFileName[255];
};

class UTILITY_CLASS CIniWriter
{
public:
	CIniWriter(LPCTSTR szFileName);
	~CIniWriter() = default;
	void WriteInteger(LPCTSTR szSection, LPCTSTR szKey, int iValue);
	void WriteFloat(LPCTSTR szSection, LPCTSTR szKey, float fltValue);
	void WriteBoolean(LPCTSTR szSection, LPCTSTR szKey, bool bolValue);
	void WriteString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szValue);
private:
	TCHAR m_szFileName[255];
};

NAMESPACE_END(util)

#endif// _INI_OPERATION_H_
