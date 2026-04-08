
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef UTILSTRCODING_EBFB2FF8_92ED_408B_9A6B_A59579E9942D_H__
#define UTILSTRCODING_EBFB2FF8_92ED_408B_9A6B_A59579E9942D_H__

#include "stdafx.h"
#include <string>
#include <global_define.h>
#include <utility/utility_dll.h>

NAMESPACE_BEGIN(util)

UTILITY_API CString int32ToCString(Int32 n);
UTILITY_API std::string uint32ToString(UInt32 n);
UTILITY_API Int32 stringToInt32(const std::string& src);
UTILITY_API Int32 cstringToInt32(LPCTSTR buff);
UTILITY_API CString utf8ToCString(const char* src);
UTILITY_API std::string cStringToUtf8(const CString& src);
UTILITY_API std::string cStringToString(const CString& src, UINT codepage = CP_UTF8);
UTILITY_API CString stringToCString(const std::string& src, UINT codepage = CP_UTF8);

UTILITY_API BOOL isIncludeChinese(const std::string& str);  // 是否包含中文
UTILITY_API CString HZ2FirstPY(IN std::string szHZ);        // 汉字转成拼音首字母
UTILITY_API CString HZ2AllPY(IN CString szHZ);              // 汉字转成全拼

UTILITY_API const std::string ws2s(const std::wstring& src);
UTILITY_API const std::wstring s2ws(const std::string& src);

UTILITY_API Int32 splitString(__in std::wstring src,
                              __in std::vector<std::wstring> _vecSpliter,
                              __out std::vector<std::wstring>& _splitList);

// 字符串转换
UTILITY_API std::string int2string(uint32_t user_id);
UTILITY_API uint32_t string2int(const std::string& value);

// 字符串替换
UTILITY_API void replace_mark(std::string& str, std::string& new_value, uint32_t& start_pos);
UTILITY_API void replace_mark(std::string& str, uint32_t new_value, uint32_t& start_pos);
UTILITY_API char* replaceStr(char* pSrc, char oldChar, char newChar);

NAMESPACE_END(util)

#endif  // UTILSTRCODING_EBFB2FF8_92ED_408B_9A6B_A59579E9942D_H__
