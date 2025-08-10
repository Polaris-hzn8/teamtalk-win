
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: �ͻ�����ͻ���֮�䴫������ ��:�������롢���ڶ���
*/

#ifndef IP2PCMDMODULE_A5B625AF_2FEF_4DDC_9A60_BC8E12EC25A1_H__
#define IP2PCMDMODULE_A5B625AF_2FEF_4DDC_9A60_BC8E12EC25A1_H__

#include "GlobalDefine.h"
#include "Modules/ModuleDll.h"
#include "Modules/ModuleBase.h"
#include "Modules/IModuleInterface.h"

NAMESPACE_BEGIN(module)
const std::string MODULE_P2PCMD_PREFIX = "P2PCmd";

//KEYID
const std::string KEY_P2PCMD_NOTIFY = MODULE_P2PCMD_PREFIX + "notify";		//�յ�P2P��Ϣ֪ͨ

//P2P��Ϣ����ö��
enum
{
	KEY_P2PCMD_SHAKEWINDOW	= 1, //����
	KEY_P2PCMD_WRITING		= 2, //��������
	KEY_P2PCMD_INNERMSG		= 3, //�������͵���Ϣ
};

//KEYID
enum
{
	KEY_P2PCMD_SHAKEWINDOW_NOTIFY = KEY_P2PCMD_SHAKEWINDOW << 16 | 1,
};

enum
{
	TAG_P2PCMD_INNERMSG_NOTIFY = KEY_P2PCMD_INNERMSG << 16 | 1,
};

enum
{
	KEY_P2PCMD_WRITING_NOTIFY = KEY_P2PCMD_WRITING << 16 | 1,
	KEY_P2PCMD_STOP_WRITING_NOTIFY = KEY_P2PCMD_WRITING << 16 | 2,
};

class IP2PCmdModule : public module::ModuleBase
					 ,public module::IPduPacketParse
{
public:
	virtual BOOL tcpSendShakeWindowCMD(IN std::string sToID) = 0;
	virtual void tcpSendWritingCMD(IN std::string sToID, IN const BOOL bWriting) = 0;
};

MODULE_API IP2PCmdModule* getP2PCmdModule();

NAMESPACE_END(module)

#endif// IP2PCMDMODULE_A5B625AF_2FEF_4DDC_9A60_BC8E12EC25A1_H__
