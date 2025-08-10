 
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef SERVERCONFIGDIALOG_7A5E8519_6F0B_4583_BAE3_DD51D7A1BE7C_H__
#define SERVERCONFIGDIALOG_7A5E8519_6F0B_4583_BAE3_DD51D7A1BE7C_H__

#include "DuiLib/UIlib.h"

using namespace DuiLib;

class ServerConfigDialog final : public WindowImplBase
{
public:
    ServerConfigDialog();
	virtual ~ServerConfigDialog();

	DUI_DECLARE_MESSAGE_MAP()
public:
	LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual void OnFinalMessage(HWND hWnd);

protected:
	void OnWindowInitialized(TNotifyUI& msg);
	void OnClick(TNotifyUI& msg);

private:
	void _InitlizeSetting();
	BOOL _ApplySetting();
private:
	CButtonUI*				m_pbtnApply;
	CTextUI*				m_pText;
	CEditUI*				m_pEditAddress;
};

#endif// SERVERCONFIGDIALOG_7A5E8519_6F0B_4583_BAE3_DD51D7A1BE7C_H__
