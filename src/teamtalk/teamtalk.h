
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
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
	BOOL _CreateUsersFolder();		//�����û�Ŀ¼
	BOOL _CreateMainDialog();		//����������
	BOOL _DestroyMainDialog();		//����������
	BOOL _IsHaveInstance();			//�ж��Ƿ��ǵ�ʵ��
	void _InitLog();
private:
	MainDialog* m_pMainDialog;
};
