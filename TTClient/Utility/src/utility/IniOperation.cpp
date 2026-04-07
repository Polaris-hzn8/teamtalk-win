
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <utility/IniOperation.h>

NAMESPACE_BEGIN(util)

/////////////////////////////CIniReader/////////////////////////////////////////////
CIniReader::CIniReader(LPCTSTR szIniPath)
{
	_tcsncpy_s(m_szIniPath, szIniPath, _TRUNCATE);
}

int CIniReader::ReadInteger(LPCTSTR szSection, LPCTSTR szKey, int iDefaultValue)
{
	return GetPrivateProfileInt(szSection, szKey, iDefaultValue, m_szIniPath);
}

float CIniReader::ReadFloat(LPCTSTR szSection, LPCTSTR szKey, float fltDefaultValue)
{
	std::wstring wstr = ReadString(szSection, szKey, std::to_wstring(fltDefaultValue).c_str());
	return static_cast<float>(_tstof(wstr.c_str()));
}

bool CIniReader::ReadBoolean(LPCTSTR szSection, LPCTSTR szKey, bool bolDefaultValue)
{
	std::wstring wstr = ReadString(szSection, szKey, bolDefaultValue ? L"true" : L"false");
	std::transform(wstr.begin(), wstr.end(), wstr.begin(), ::towlower);
	if (wstr == L"true" || wstr == L"1")
		return true;
	return false;
}

CString CIniReader::ReadString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefaultValue)
{
	size_t bufferSize = 1024;
	std::vector<TCHAR> buffer(bufferSize);
	DWORD nCopied = 0;
	while (true)
	{
		nCopied = GetPrivateProfileString(szSection, szKey, szDefaultValue, buffer.data(), static_cast<DWORD>(buffer.size()), m_szIniPath);
		if (nCopied < buffer.size() - 1)
			break;
		bufferSize *= 2;
		buffer.resize(bufferSize);
	}
	return CString(buffer.data(), nCopied);
}

////////////////////////////CIniWriter//////////////////////////////////////////////
CIniWriter::CIniWriter(LPCTSTR szIniPath)
{
	_tcsncpy_s(m_szIniPath, szIniPath, _TRUNCATE);
}

void CIniWriter::WriteInteger(LPCTSTR szSection, LPCTSTR szKey, int iValue)
{
	WriteString(szSection, szKey, std::to_wstring(iValue).c_str());
}

void CIniWriter::WriteFloat(LPCTSTR szSection, LPCTSTR szKey, float fltValue)
{
	WriteString(szSection, szKey, std::to_wstring(fltValue).c_str());
}

void CIniWriter::WriteBoolean(LPCTSTR szSection, LPCTSTR szKey, bool bolValue)
{
	WriteString(szSection, szKey, bolValue ? L"true" : L"false");
}

void CIniWriter::WriteString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szValue)
{
	WritePrivateProfileString(szSection, szKey, szValue, m_szIniPath);
}

NAMESPACE_END(util)
