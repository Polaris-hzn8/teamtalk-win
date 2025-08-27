
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: �������ģ��ӿڣ��Դ��麯��ʵ�֣�
*/

#ifndef IEMOTIONMODULE_8E431B43_8F05_4934_8B5B_BB839730F3A6_H__
#define IEMOTIONMODULE_8E431B43_8F05_4934_8B5B_BB839730F3A6_H__

#include "GlobalDefine.h"
#include "Modules/ModuleDll.h"
#include "Modules/ModuleBase.h"

NAMESPACE_BEGIN(module)

const std::string MODULE_EMOTION_PREFIX = "Emotion";
const std::string KEY_EMOTION_SELECTED = MODULE_EMOTION_PREFIX + "selected";

class EmotionParam
{
public:
	std::string			 sid;
	CString				 strPath;
};

class MODULE_API IEmotionModule : public module::ModuleBase
{
public:
	// ��ʾ���鴰��
	virtual void showEmotionDialog(IN std::string sid, IN POINT pt) = 0;
	// ����ID��ȡ��������
	virtual BOOL getEmotionNameByID(IN CString ID, OUT CString& csPath) = 0;
	// ���ݱ������ƻ�ȡ����ID
	virtual BOOL getEmotionIDByName(IN CString csPath, OUT CString& ID) = 0;
	// ��ȡ��ǰ��ʾ���ڵĻỰID
	virtual std::string  getCurEmotionWndSessionId(void) = 0;
	// ��ȡ���б����ļ����ļ����б�
	virtual void getAllEmotionFileNames(OUT std::list<CString>& nameList) = 0;
};

MODULE_API IEmotionModule* getEmotionModule();

NAMESPACE_END(module)

#endif// IEMOTIONMODULE_8E431B43_8F05_4934_8B5B_BB839730F3A6_H__


