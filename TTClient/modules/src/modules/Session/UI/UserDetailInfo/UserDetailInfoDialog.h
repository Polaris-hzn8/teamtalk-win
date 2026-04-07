
#ifndef USERDETAILINFODIALOG_9D88F1FB_337B_4EF3_8282_4B28D272199E_H__
#define USERDETAILINFODIALOG_9D88F1FB_337B_4EF3_8282_4B28D272199E_H__

#include <DuiLib/UIlib.h>
#include <global_define.h>
#include <memory>
using namespace DuiLib;
namespace module
{
	struct IHttpOperation;
}

class UserDetailInfoDialog : public WindowImplBase
{
public:
    UserDetailInfoDialog(IN std::string sid);
    ~UserDetailInfoDialog() = default;

	LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void OnFinalMessage(HWND hWnd);
	DUI_DECLARE_MESSAGE_MAP()

	void onHttpGetAvatarCallback(std::shared_ptr<void> param);
private:
	void OnWindowInitialized(TNotifyUI& msg);
	void OnClick(TNotifyUI& msg);

	void _refreshAvatar(IN const std::string& avatarPath);
private:
	std::string m_sid;
	CControlUI* m_AvatarUI;
	module::IHttpOperation*		m_pDownHttpOper = 0;
};

#endif// USERDETAILINFODIALOG_9D88F1FB_337B_4EF3_8282_4B28D272199E_H__
