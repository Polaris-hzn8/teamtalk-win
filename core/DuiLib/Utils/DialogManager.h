/*
  Reviser: Polaris_hzn8
  Email: lch2022fox@163.com
  Github: https://github.com/Polaris-hzn8
  brief: duilib´°¿Ú¹ÜÀíÆ÷
*/

#ifndef DIALOGMANAGER_1119417E_2736_419F_B096_964E2676382E_H__
#define DIALOGMANAGER_1119417E_2736_419F_B096_964E2676382E_H__

#include <vector>
#include "GlobalDefine.h"
#include "../core/DuiLib/UIlib.h"

NAMESPACE_BEGIN(DuiLib)

class UILIB_API DialogManager
{
public:
    DialogManager();
    ~DialogManager();
	static DialogManager* getInstance();
public:
	void registerDialog(WindowImplBase* pDialog);
	void unRegisterDialog(WindowImplBase* pDialog);
	void closeAllDialogs();

private:
	#pragma warning(disable : 4251)
	std::vector<WindowImplBase*>			m_vecDialogs;
};

NAMESPACE_END(DuiLib)

#endif// DIALOGMANAGER_1119417E_2736_419F_B096_964E2676382E_H__
