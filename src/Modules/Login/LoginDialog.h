
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 客户端主登录窗口
*/

#ifndef LOGINWND_8DCB20F9_062A_47AC_8C5C_7DD1ED11C9E8_H__
#define LOGINWND_8DCB20F9_062A_47AC_8C5C_7DD1ED11C9E8_H__

#include "GlobalDefine.h"
#include "DuiLib/UIlib.h"
#include <memory>

using namespace DuiLib;

class LoginDialog final: public WindowImplBase
{
public:
    LoginDialog();
    virtual ~LoginDialog();

	DUI_DECLARE_MESSAGE_MAP()
public:
	LPCTSTR GetWindowClassName() const;

	void InitWindow();
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual void OnFinalMessage(HWND hWnd);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	void OnOperationCallback(std::shared_ptr<void> param);
	void OnHttpCallbackOperation(std::shared_ptr<void> param);
protected:
	void OnWindowInitialized(TNotifyUI& msg);
	void OnClick(TNotifyUI& msg);
	void OnTextChanged(TNotifyUI& msg);
	void OnSetFocus(TNotifyUI& msg);
private:
	void _DoLogin();
	void _Initlize();
	BOOL _CreateUsersFolder();

private:
	CTextUI*					m_ptxtTip;
	CEditUI*					m_pedtUserName;
	CEditUI*					m_pedtPassword;
	CButtonUI*					m_pBtnLogin;
	CButtonUI*					m_pBtnSysSetting;
	CCheckBoxUI*				m_pChkRememberPWD;

	BOOL						m_bPassChanged;
	//CWndShadow					m_WndShadow;//阴影窗口
};

#endif// LOGINWND_8DCB20F9_062A_47AC_8C5C_7DD1ED11C9E8_H__
