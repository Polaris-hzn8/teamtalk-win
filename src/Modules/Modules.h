
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: Modules DLLͷ�ļ�
*/

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"

// CModulesApp
// �йش���ʵ�ֵ���Ϣ������� Modules.cpp
//

class CModulesApp : public CWinApp
{
public:
	CModulesApp();
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
