
#ifndef FILETRANSFERDIALOG_624E545F_4732_4817_913B_C929D5B87C9D_H__
#define FILETRANSFERDIALOG_624E545F_4732_4817_913B_C929D5B87C9D_H__

#include <DuiLib/UIlib.h>
#include <global_define.h>
#include <modules/Base/ModuleObserver.h>
using namespace DuiLib;

class TransferFileEntity;
class FileTransferDialog : public WindowImplBase
{
public:
    FileTransferDialog();
    virtual ~FileTransferDialog();

	LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void OnFinalMessage(HWND hWnd);
	DUI_DECLARE_MESSAGE_MAP()

public:
	void MKOForFileTransferModuleCallBack(const std::string& keyId, MKO_TUPLE_PARAM mkoParam);

public:
	void AddTransderItemToList(IN std::string& id);
	CListContainerElementUI* AddTransderItemToList(IN TransferFileEntity fileInfo);
	CListContainerElementUI* GetTransferItemById(std::string& id);

	void OnWindowInitialized(TNotifyUI& msg);
	void OnClick(TNotifyUI& msg);

	void _UpdateItemButtons(
		IN CListContainerElementUI* pListElement,
		IN bool bShowbtnOpenFile,
		IN bool bShowbtnOpenFolder,
		IN bool bShowbtnAccpet,
		IN bool bShowbtnRefuse,
		IN bool bShowbtnCancel);

	void _UpdateFileTransferState(
		IN CListContainerElementUI* pListElement,
		IN const std::string& keyId);

	CListContainerElementUI* _GetItemBySid(IN std::string sid);
public:
	CListUI*					m_plstFileTransfer;
	CProgressUI*				m_pprsTransProgress;
};

#endif// FILETRANSFERDIALOG_624E545F_4732_4817_913B_C929D5B87C9D_H__
