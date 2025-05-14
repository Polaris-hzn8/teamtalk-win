
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef LOGINMODULE_IMPL_9020B75A_241C_4250_94F5_66F0EC1C9DD9_H__
#define LOGINMODULE_IMPL_9020B75A_241C_4250_94F5_66F0EC1C9DD9_H__

#include "Modules/ILoginModule.h"

class ReloginManager;
class LoginModule_Impl final : public module::ILoginModule
{
public:
	LoginModule_Impl();
    virtual ~LoginModule_Impl();
	virtual void onPacket(imcore::TTPBHeader& header, std::string& pbBody);
public:
	virtual BOOL showLoginDialog();
	virtual void notifyLoginDone();
	virtual void relogin(BOOL bForce);
	virtual BOOL isOfflineByMyself()const;
	virtual void setOfflineByMyself(BOOL b);

private:
	void _kickUserResponse(IN std::string& pbBody);// ·þÎñÆ÷¶Ë²ð°ü
private:
	ReloginManager*				m_pReloginManager;
	BOOL						m_bIsOfflineByMyself;
};

#endif// LOGINMODULE_IMPL_9020B75A_241C_4250_94F5_66F0EC1C9DD9_H__
