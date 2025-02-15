
/**
* Copyright (C) 2024 Polaris-hzn8 / LuoChenhao
*
* Author: luochenhao
* Email: lch2022fox@163.com
* Time: Tue 08 Oct 2024 00:28:16 CST
* Github: https://github.com/Polaris-hzn8
* Src code may be copied only under the term's of the Apache License
* Please visit the http://www.apache.org/licenses/ Page for more detail.
* brief: 多语言支持工具类 利用windows IniApi实现
**/

#ifndef MULTILINGUAL_93AF83ED_9E20_45F1_8C1A_48CA7C6D3FF9_H__
#define MULTILINGUAL_93AF83ED_9E20_45F1_8C1A_48CA7C6D3FF9_H__

#include "GlobalDefine.h"
#include "utility/utilityDll.h"

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

#endif// MULTILINGUAL_93AF83ED_9E20_45F1_8C1A_48CA7C6D3FF9_H__
