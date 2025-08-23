#include "stdafx.h"
#include "teamtalk.h"
#include "UI/MainDialog.h"
#include "GlobalConfig.h"
#include "versioninfo.h"
#include "google/protobuf/stubs/common.h"
#include "utility/utilCommonAPI.h"
#include "utility/Multilingual.h"
#include "utility/utilStrCodingAPI.h"
#include "Modules/IHttpPoolModule.h"
#include "Modules/ILoginModule.h"
#include "Modules/IMiscModule.h"
#include "Modules/ISysConfigModule.h"
#include "Modules/ITcpClientModule.h"
#include "Modules/UIEventManager.h"
#include "network/OperationManager.h"
#include "network/ImCore.h"

CteamtalkApp theApp;

CteamtalkApp::CteamtalkApp()
:m_pMainDialog(0) {
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

BOOL CteamtalkApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	_InitLog();

	// 版本兼容性校验
	// 验证编译与链接使用的Protobuf库版本是否兼容
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	
	LOG__(APP, _T("===================================VersionNO:%d======BulidTime：%s--%s=========================="),
		TEAMTALK_VERSION,
		util::utf8ToCString(__DATE__),
		util::utf8ToCString(__TIME__));

	if (!__super::InitInstance())
	{
		LOG__(ERR, _T("__super::InitInstance failed."));
		return FALSE;
	}
	AfxEnableControlContainer();// ActiveX控件支持

	//if (_IsHaveInstance())
	//{
	//	LOG__(ERR, _T("Had one instance,this will exit"));
	//	HWND hwndMain = FindWindow(_T("TeamTalkMainDialog"), NULL);
	//	if (hwndMain)
	//	{
	//		::SendMessage(hwndMain, WM_START_MOGUTALKINSTANCE, NULL, NULL);
	//	}
	//	return FALSE;
	//}

	// 网络事件循环
	// 1.启动任务处理线程
	// 2.启动IO处理线程监听IO读写事件
	if (!imcore::IMLibCoreRunEvent())
	{
		LOG__(ERR, _T("start imcore lib failed!"));
	}
	LOG__(APP, _T("start imcore lib done"));

	//start ui event
	// 启动ui事件代理窗口，从系统消息队列中获取消息并处理 一般事件和定时事件
	if (module::getEventManager()->startup() != imcore::IMCORE_OK)
	{
		LOG__(ERR, _T("start ui event failed"));
	}
	LOG__(APP, _T("start ui event done"));

	//create user folders
	_CreateUsersFolder();
	
	//duilib初始化
	CPaintManagerUI::SetInstance(AfxGetInstanceHandle());
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("..\\gui\\"));
	::CoInitialize(NULL);
	::OleInitialize(NULL);

	// 登录服务器信息配置（模态对话框）
	module::TTConfig* pCfg = module::getSysConfigModule()->getSystemConfig();
	if (pCfg && pCfg->loginServIP.IsEmpty())
	{
		if (!module::getSysConfigModule()->showServerConfigDialog(NULL))
		{
			LOG__(APP, _T("server config canceled"));
			return FALSE;
		}
	}

	if (!module::getLoginModule()->showLoginDialog())
	{
		LOG__(ERR, _T("login canceled"));
		return FALSE;
	}
	LOG__(APP,_T("login success"));

	//创建主窗口
	if (!_CreateMainDialog())
	{
		LOG__(ERR, _T("Create MianDialog failed"));
		return FALSE;
	}
	LOG__(APP, _T("Create MianDialog done"));

	// 启用Duilib的消息循环
	CPaintManagerUI::MessageLoop();
	CPaintManagerUI::Term();

	return TRUE;
}

BOOL CteamtalkApp::_DestroyMainDialog()
{
	delete m_pMainDialog;
	m_pMainDialog = 0;
	return TRUE;
}

BOOL CteamtalkApp::_CreateMainDialog()
{
	m_pMainDialog = new MainDialog();
	PTR_FALSE(m_pMainDialog);
	CString csTitle = util::getMultilingual()->getStringById(_T("STRID_GLOBAL_CAPTION_NAME"));
	if (!m_pMainDialog->Create(NULL, csTitle
		, UI_CLASSSTYLE_DIALOG, WS_EX_STATICEDGE /*| WS_EX_APPWINDOW*/ | WS_EX_TOOLWINDOW, 0, 0, 600, 800))
		return FALSE;
	m_pMainDialog->BringToTop();

	return TRUE;
}

BOOL CteamtalkApp::ExitInstance()
{
	LOG__(APP, _T("Exit Instance"));

	//close httppool
	module::getHttpPoolModule()->shutdown();
	LOG__(APP, _T("close http pool done"));
	//close network socket io
	module::getTcpClientModule()->shutdown();
	LOG__(APP, _T("close tcpclient socket done"));
	//stop imcore lib 
	imcore::IMLibCoreStopEvent();
	LOG__(APP, _T("stop imcore lib done"));

	module::getEventManager()->shutdown();
	LOG__(APP, _T("stop ui event done"));

	_DestroyMainDialog();
	LOG__(APP,_T("MainDialog Destory done"));	

	WSACleanup();

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	LOG__(APP, _T("Exit OK"));

	YAOLOG_EXIT;
	return __super::ExitInstance();
}

BOOL CteamtalkApp::_CreateUsersFolder()
{
	module::IMiscModule* pModule = module::getMiscModule();
	// 用户目录
	if (!util::createAllDirectories(pModule->getUsersDir()))
	{
		LOG__(ERR, _T("_CreateUsersFolder users direcotry failed!"));
		return FALSE;
	}
	// 下载目录
	if (!util::createAllDirectories(pModule->getDownloadDir()))
	{
		LOG__(ERR, _T("_CreateUsersFolder download direcotry failed!"));
		return FALSE;
	}
	return TRUE;
}

#ifdef _DEBUG
	#define  AppSingletonMutex _T("{7A666640-EDB3-44CC-954B-0C43F35A2E17}")
#else
	#define  AppSingletonMutex _T("{5676532A-6F70-460D-A1F0-81D6E68F046A}")
#endif
BOOL CteamtalkApp::_IsHaveInstance()
{
	HANDLE hMutex = ::CreateMutex(NULL, TRUE, AppSingletonMutex);
	if (hMutex != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(0, _T("上次程序运行还没完全退出，请稍后再启动！"), _T("TeamTalk"), MB_OK);
		return TRUE;
	}

	return FALSE;
}

void CteamtalkApp::_InitLog()
{
	std::string logConfig = util::cStringToString(util::getAppPath()) + "\\ttlogconfig.ini";

	YAOLOG_INIT;
	YAOLOG_CREATE(APP, true, YaoUtil::LOG_TYPE_TEXT);
	YAOLOG_CREATE(NET, true, YaoUtil::LOG_TYPE_TEXT);
	YAOLOG_CREATE(DEBG, true, YaoUtil::LOG_TYPE_TEXT);
	YAOLOG_CREATE(ERR, true, YaoUtil::LOG_TYPE_TEXT);
	YAOLOG_CREATE(SOCK, true, YaoUtil::LOG_TYPE_FORMATTED_BIN);
	YAOLOG_SET_ATTR_FROM_CONFIG_FILE(APP, logConfig.c_str());
	YAOLOG_SET_ATTR_FROM_CONFIG_FILE(NET, logConfig.c_str());
	YAOLOG_SET_ATTR_FROM_CONFIG_FILE(DEBG, logConfig.c_str());
	YAOLOG_SET_ATTR_FROM_CONFIG_FILE(ERR, logConfig.c_str());
	YAOLOG_SET_ATTR_FROM_CONFIG_FILE(SOCK, logConfig.c_str());
}
