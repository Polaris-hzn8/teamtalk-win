
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: ������֧�ֹ����� ����windows Ini�ļ�ʵ��
*/

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
