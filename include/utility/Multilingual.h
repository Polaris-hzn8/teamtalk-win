
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: ������֧�ֹ����� ����windows Ini�ļ�ʵ��
*/

#ifndef _MULTILINGUAL_H_
#define _MULTILINGUAL_H_

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

#endif// _MULTILINGUAL_H_
