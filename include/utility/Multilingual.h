
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 多语言支持工具类 利用windows Ini文件实现
*/

#ifndef _MULTILINGUAL_H_
#define _MULTILINGUAL_H_

#include "GlobalDefine.h"
#include "utility/utility_dll.h"

NAMESPACE_BEGIN(util)

class UTILITY_CLASS Multilingual
{
public:
    Multilingual();
    ~Multilingual();
public:
	CString getStringById(LPCTSTR strID);
};
extern UTILITY_API Multilingual* getMultilingual();

NAMESPACE_END(util)

#endif// _MULTILINGUAL_H_
