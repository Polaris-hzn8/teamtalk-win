
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"

class MainDialog;
class CteamtalkApp : public CWinApp
{
public:
	CteamtalkApp();
public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
private:
	BOOL _CreateUsersFolder();		//创建用户目录
	BOOL _CreateMainDialog();		//创建主窗口
	BOOL _DestroyMainDialog();		//销毁主窗口
	BOOL _IsHaveInstance();			//判断是否是单实例
	void _InitLog();
private:
	MainDialog* m_pMainDialog;
};
