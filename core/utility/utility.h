// utility.h : utility DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

class CutilityApp : public CWinApp
{
public:
	CutilityApp();
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
