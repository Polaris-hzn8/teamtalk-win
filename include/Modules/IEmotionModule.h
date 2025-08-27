
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 表情管理模块接口（以纯虚函数实现）
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
	// 显示表情窗口
	virtual void showEmotionDialog(IN std::string sid, IN POINT pt) = 0;
	// 根据ID获取表情名称
	virtual BOOL getEmotionNameByID(IN CString ID, OUT CString& csPath) = 0;
	// 根据表情名称获取表情ID
	virtual BOOL getEmotionIDByName(IN CString csPath, OUT CString& ID) = 0;
	// 获取当前显示窗口的会话ID
	virtual std::string  getCurEmotionWndSessionId(void) = 0;
	// 获取所有表情文件的文件名列表
	virtual void getAllEmotionFileNames(OUT std::list<CString>& nameList) = 0;
};

MODULE_API IEmotionModule* getEmotionModule();

NAMESPACE_END(module)

#endif// IEMOTIONMODULE_8E431B43_8F05_4934_8B5B_BB839730F3A6_H__


