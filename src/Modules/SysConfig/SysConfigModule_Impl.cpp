
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#include "stdafx.h"
#include "utility/IniOperation.h"
#include "utility/utilCommonAPI.h"
#include "utility/utilStrCodingAPI.h"
#include "Modules/IMiscModule.h"
#include "Modules/IModuleInterface.h"
#include "Modules/Session/Operation/DownloadAvatarHttpOperation.h"
#include "SysConfigDialog.h"
#include "ServerConfigDialog.h"
#include "SysConfigModule_Impl.h"

namespace module
{
	ISysConfigModule* getSysConfigModule()
	{
		static SysConfigModule_Impl module;
		return &module;
	}
}

namespace
{
	const CString g_config = _T("config.dat");
	const CString g_account_config = _T("accountConfig.ini");
	const CString g_flag = _T("$Teamtalk");
}

SysConfigModule_Impl::SysConfigModule_Impl() : m_bSysConfigDialogFlag(FALSE)
{
	//m_Config.sysBaseFlag |= module::BASE_FLAG_NOTIPWHENNEWMSG;//TODO：由于飘窗会抢焦点，默认不打开飘窗
	m_Config.sysBaseFlag |= module::BASE_FLAG_NOSOUNDWHENMSG;

	_loadData();
}

SysConfigModule_Impl::~SysConfigModule_Impl()
{
	_saveData();
}

BOOL SysConfigModule_Impl::_loadData()
{
	CString fileName = util::getAppPath() + g_config;
	if (!PathFileExists(fileName))
	{
		LOG__(ERR, _T("_loadData system config file is not exist"));
		_saveData();
		return FALSE;
	}

	CFile file;
	try
	{
		if (FALSE == file.Open(fileName, CFile::modeRead))
		{
			LOG__(ERR,_T("_loadData open system config failed,%s"), fileName);
			return FALSE;
		}

		CArchive ar(&file, CArchive::load);
		_unMarshal(ar);
		ar.Close();
		file.Close();
	}
	catch(...)
	{
		LOG__(ERR,_T("_loadData open system config unknown exception,%s"), fileName);
		file.Close();
		::DeleteFile(fileName);
		_saveData();
		return FALSE;
	}

	return TRUE;
}

BOOL SysConfigModule_Impl::_saveData()
{
	CString fileName = util::getAppPath() + g_config;

	CFile file;
	try
	{
		if (FALSE == file.Open(fileName, CFile::modeCreate | CFile::modeWrite))
		{
			LOG__(ERR, _T("_saveData open system config failed,%s"), fileName);
			return FALSE;
		}
		CArchive ar(&file, CArchive::store);
		_marshal(ar);
		ar.Close();
		file.Flush();
		file.Close();
	}
	catch(...)
	{
		LOG__(ERR,_T("_saveData open system config unknown exception,%s"), fileName);
		file.Close();
		return FALSE;
	}

	return TRUE;
}

void SysConfigModule_Impl::_unMarshal(CArchive& ar)
{
	CString csFlag(g_flag);
	ar >> csFlag;
	ar >> m_Config.version;

	ar >> m_Config.isRememberPWD;
	ar >> m_Config.userName;
	CString csTemp;
	ar >> csTemp;
	m_Config.password = util::cStringToString(csTemp);
	ar >> m_Config.loginServIP;
	ar >> m_Config.sysBaseFlag;
	ar >> m_Config.sysSoundTypeBaseFlag;
	//向后兼容demo
	//if (m_pConfig.version >= 2)
	//{
	//	ar >> m_pConfig.a2;
	//}
	//if (m_pConfig.version >= 3)
	//{
	//	ar >> m_pConfig.a3;
	//}
	//if (m_pConfig.version >= 4)
	//{
	//	ar >> m_pConfig.a4;
	//}
}

void SysConfigModule_Impl::_marshal(CArchive& ar)
{
	CString csFlag(g_flag);
	ar << csFlag;
	ar << module::SYSCONFIG_VERSIONI;

	ar << m_Config.isRememberPWD;
	ar << m_Config.userName;
	ar << util::stringToCString(m_Config.password);
	ar << m_Config.loginServIP;
	ar << m_Config.sysBaseFlag;
	ar << m_Config.sysSoundTypeBaseFlag;
	//向后兼容demo
	//ar << m_pConfig.a2;
	//ar << m_pConfig.a3;
	//ar << m_pConfig.a4;
}

module::TTConfig* SysConfigModule_Impl::getSystemConfig()
{
	return &m_Config;
}

BOOL SysConfigModule_Impl::saveData()
{
	return _saveData();
}

std::string SysConfigModule_Impl::userID() const
{
	return m_Config.userId;
}

CString SysConfigModule_Impl::UserID() const
{
	return m_Config.csUserId;
}

UInt32 SysConfigModule_Impl::userId() const
{
	return util::stringToInt32(m_Config.userId);
}

void SysConfigModule_Impl::showSysConfigDialog(HWND hParentWnd)
{
	if (m_bSysConfigDialogFlag)
	{
		return;
	}
	m_bSysConfigDialogFlag = TRUE;
	SysConfigDialog* pSysConfigDialog = new SysConfigDialog();
	pSysConfigDialog->Create(hParentWnd, _T("SysConfigDialog")
		, UI_CLASSSTYLE_DIALOG, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 0, 0);
	pSysConfigDialog->CenterWindow();
	pSysConfigDialog->ShowWindow(true);
}

void SysConfigModule_Impl::setSysConfigDialogFlag(BOOL bIsExist)
{
	m_bSysConfigDialogFlag = bIsExist;
}

BOOL SysConfigModule_Impl::showServerConfigDialog(HWND hParentWnd)
{
	BOOL bRet = FALSE;
	ServerConfigDialog* pServerConfigDialog = new ServerConfigDialog();
	PTR_FALSE(pServerConfigDialog);
	pServerConfigDialog->Create(hParentWnd, _T("服务器配置"), UI_CLASSSTYLE_DIALOG, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 0, 0);
	pServerConfigDialog->CenterWindow();
	bRet = (IDOK == pServerConfigDialog->ShowModal());
	return bRet;
}

UInt32 SysConfigModule_Impl::getUserInfoLatestUpdateTime(void)
{
	CString strPath = module::getMiscModule()->getTTCommonAppdataUserDir() + g_account_config;
	util::CIniReader iniReader(strPath);
	UInt32 time = 0;
	time = iniReader.ReadInteger(L"user", L"LastUpdateTime", time);
	return time;
}

void SysConfigModule_Impl::saveUserInfoLatestUpdateTime(IN const UInt32 nLatestUpdateTime)
{
	CString strPath = module::getMiscModule()->getTTCommonAppdataUserDir() + g_account_config;
	util::CIniWriter iniWriter(strPath);
	iniWriter.WriteInteger(L"user", L"LastUpdateTime", nLatestUpdateTime);
}

UInt32 SysConfigModule_Impl::getRecentSessionLatestUpdateTime(void)
{
	CString strPath = module::getMiscModule()->getTTCommonAppdataUserDir() + g_account_config;
	util::CIniReader iniReader(strPath);
	UInt32 time = 0;
	time = iniReader.ReadInteger(L"recentSession", L"LastUpdateTime", time);
	return time;
}

void SysConfigModule_Impl::saveRecentSessionLatestUpdateTime(IN const UInt32 nLatestUpdateTime)
{
	CString strPath = module::getMiscModule()->getTTCommonAppdataUserDir() + g_account_config;
	util::CIniWriter iniWriter(strPath);
	iniWriter.WriteInteger(L"recentSession", L"LastUpdateTime", nLatestUpdateTime);
}

BOOL SysConfigModule_Impl::getImage(
	IN std::string sid,
	IN std::string url,
	IN BOOL bGrayScale,
	IN std::string& format,
	IN module::IOperationDelegate callback,
	OUT std::string& sLocalPath)
{
	UInt32 hashcode = util::hash_BKDR((sid + format).c_str());
	module::ImImageEntity imageEntity;
	module::getDatabaseModule()->sqlGetImImageEntityByHashcode(hashcode, imageEntity);
	CString csLocalPath = module::getMiscModule()->getDownloadDir() + util::stringToCString(imageEntity.filename);
	if (!imageEntity.filename.empty() && PathFileExists(csLocalPath))
	{/* 本地磁盘已存在 */
		sLocalPath = util::cStringToString(csLocalPath);
		return TRUE;
	}
	else
	{/* 本地磁盘不存在 - 服务器下载 */
		//if (module::getSysConfigModule()->userID() == sid)
		//{
		//	format = "_60x60";
		//}
		//DownloadImgHttpOperation* pOper = new DownloadImgHttpOperation(sid, url, bGrayScale, format, BIND_CALLBACK_1(callback));
		//module::getHttpPoolModule()->pushHttpOperation(pOper);
	}
	return FALSE;
}

UInt32 SysConfigModule_Impl::getDepartmentInfoLatestUpdateTime(void)
{
	CString strPath = module::getMiscModule()->getTTCommonAppdataUserDir() + g_account_config;
	util::CIniReader iniReader(strPath);
	UInt32 time = 0;
	time = iniReader.ReadInteger(L"department", L"LastUpdateTime", time);
	return time;
}

void SysConfigModule_Impl::saveDepartmentInfoLatestUpdateTime(IN const UInt32 nLatestUpdateTime)
{
	CString strPath = module::getMiscModule()->getTTCommonAppdataUserDir() + g_account_config;
	util::CIniWriter iniWriter(strPath);
	iniWriter.WriteInteger(L"department", L"LastUpdateTime", nLatestUpdateTime);
}
