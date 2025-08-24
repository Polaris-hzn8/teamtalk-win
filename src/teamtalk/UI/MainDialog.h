
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 应用主窗口teamtalk
*/

#ifndef _MAINDIALOG_H_
#define _MAINDIALOG_H_

#include "GlobalDefine.h"
#include "Modules/ModuleObserver.h"

#define WM_START_MOGUTALKINSTANCE	WM_USER + 101
#define WM_TRAYICON_NOTIFY			WM_USER + 1002

const UInt16  TIMER_TRAYEMOT = 1;//系统托盘闪烁timer

enum
{
	ICON_TRAY_LOGO = 0,
	ICON_TRAY_NEWMSG,
	ICON_TRAY_LEAVE,
	ICON_TRAY_OFFLINE,
	ICON_COUNT,
};

enum BalloonStyle
{
	BALLOON_WARNING,
	BALLOON_ERROR,
	BALLOON_INFO,
	BALLOON_NONE,
	BALLOON_USER,
};

class CNotifyIconData : public NOTIFYICONDATA
{
public:
	CNotifyIconData()
	{
		memset(this, 0, sizeof(NOTIFYICONDATA));
		cbSize = sizeof(NOTIFYICONDATA);
	}
};

class MainDialog final : public WindowImplBase
{
public:
    MainDialog();
    virtual ~MainDialog();
	DUI_DECLARE_MESSAGE_MAP()
public:
	LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual void InitWindow();
	virtual void OnFinalMessage(HWND hWnd);
    virtual void Notify(TNotifyUI& msg);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	// MainDialog
	void UpdateTotalUnReadMsgCount(void);	//更新总的未读计数
	void FreshMySignature(void);
	//void OnCheckUpdateSucc(WPARAM wparam, LPARAM lparam);
	//void OnCheckUpdate(WPARAM wparam, LPARAM lparam);

	// TrayIcon
	BOOL InstallIcon(LPCTSTR lpszToolTip, HICON hIcon, UINT nID, BOOL bReInstall = FALSE);
	BOOL RemoveIcon();
	BOOL SetTrayIcon(HICON hIcon);
	BOOL HideIcon(void);
	BOOL ShowIcon();
	BOOL IsIconInstalled() { return m_bInstalled; }
	BOOL SetTrayTooltipText(LPCTSTR pszTooltipText);
	BOOL SetBalloonDetails(LPCTSTR pszBalloonText, LPCTSTR pszBalloonCaption, BalloonStyle style = BALLOON_INFO, UINT nTimeout = 1000, HICON hUserIcon = NULL, BOOL bNoSound = FALSE);
	BOOL SetVersion(UINT uVersion);
	DWORD GetShellVersion(void);

	// Event
	void MKOForTcpClientModuleCallBack(const std::string& keyId, MKO_TUPLE_PARAM mkoParam);
	void MKOForLoginModuleCallBack(const std::string& keyId, MKO_TUPLE_PARAM mkoParam);
	void MKOForUserListModuleCallBack(const std::string& keyId, MKO_TUPLE_PARAM mkoParam);
	void MKOForSessionModuleCallBack(const std::string& keyId, MKO_TUPLE_PARAM mkoParam);
	void StartNewMsgTrayEmot();				//开始系统托盘闪烁
	void StopNewMsgTrayEmot();				//停止系统托盘闪烁

private:
	// MainDialog
	void Initilize();
	void CreateTrayIcon();
	void LoadIcons();
	void UpdateLineStatus(UInt8 status);
	void SetTrayIconIndex(int nIndex);

	void OnHotkey(__in WPARAM wParam, __in LPARAM lParam);
	void OnWindowInitialized(TNotifyUI& msg);
	void OnTextChanged(TNotifyUI& msg);
	void OnClick(TNotifyUI& msg);
	void OnCopyData(IN COPYDATASTRUCT* pCopyData);

	// TrayIcon
	void OnTrayIconNotify(WPARAM wParam, LPARAM lParam);

	// Event
	void OnMenuClicked(IN const CString& itemName, IN const CString& strLparam);
private:
	CButtonUI*				m_pbtnSysConfig;
	CButtonUI*				m_pbtnOnlineStatus;
	CButtonUI*				m_pbtnMyFace;
	CButtonUI*				m_pbtnClose;
	CButtonUI*				m_pbtnMinMize;
	CTextUI*				m_ptxtUname;
    CTextUI*				m_pTextUnreadMsgCount;	//总的未读计数
    CEditUI*	            m_pEditSignature;		//个性签名

	HICON                   m_hIcons[ICON_COUNT];	//Icon对象数组
	CNotifyIconData			m_niData;
	BOOL					m_bInstalled;
	BOOL					m_bHidden;
	DWORD					m_dwShellVersion;
};

#endif// _MAINDIALOG_H_


