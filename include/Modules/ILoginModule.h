
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef ILOGINMODULE_2BB11F1D_3E16_44D3_92FB_6CAE04D48B6B_H__
#define ILOGINMODULE_2BB11F1D_3E16_44D3_92FB_6CAE04D48B6B_H__

#include <string>
#include "GlobalDefine.h"
#include "Modules/ModuleDll.h"
#include "Modules/ModuleBase.h"
#include "Modules/IModuleInterface.h"

NAMESPACE_BEGIN(module)
const std::string MODULE_LOING_PREFIX = "login";

//KEYID
const std::string KEY_LOGIN_KICKOUT = MODULE_LOING_PREFIX + "kickout";				//踢出处理
const std::string KEY_LOGIN_RELOGINOK = MODULE_LOING_PREFIX + "reloginok";			//relogin成功通知

class MODULE_API ILoginModule :
	public module::ModuleBase,
	public module::IPduPacketParse
{
public:
	virtual BOOL showLoginDialog() = 0;
	virtual void notifyLoginDone() = 0;
	virtual void relogin(BOOL bForce) = 0;// 断线重连

	virtual BOOL isOfflineByMyself()const = 0;
	virtual void setOfflineByMyself(BOOL b) = 0;
};

MODULE_API ILoginModule* getLoginModule();

NAMESPACE_END(module)

#endif// ILOGINMODULE_2BB11F1D_3E16_44D3_92FB_6CAE04D48B6B_H__
