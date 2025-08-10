
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: Modules DLL头文件
*/

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"

// CModulesApp
// 有关此类实现的信息，请参阅 Modules.cpp
//

class CModulesApp : public CWinApp
{
public:
	CModulesApp();
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
