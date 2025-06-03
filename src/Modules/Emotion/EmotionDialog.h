
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef UIEMOTION_5122008B_3DA1_4CCC_9A2E_474D1CF7C234_H__
#define UIEMOTION_5122008B_3DA1_4CCC_9A2E_474D1CF7C234_H__

#include "DuiLib/UIlib.h"
using namespace DuiLib;

class EmotionDialog: public WindowImplBase
{
public:
    EmotionDialog();
    virtual ~EmotionDialog();

public:
	void OnFinalMessage(HWND /*hWnd*/);
	void Init();
	void OnPrepare();
	LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);

	void ShowWindow(IN POINT pt ,bool bShow);
protected:
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual LPCTSTR GetWindowClassName() const;
	virtual UINT GetClassStyle() const;
	virtual LONG GetStyle();
	virtual void Notify(TNotifyUI& msg);
private:

};

#endif// UIEMOTION_5122008B_3DA1_4CCC_9A2E_474D1CF7C234_H__
