
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 
*/

#ifndef EMOTIONMODULE_IMPL_9432EBF5_DD5E_4C01_BF4B_A8D3E1E11CB9_H__
#define EMOTIONMODULE_IMPL_9432EBF5_DD5E_4C01_BF4B_A8D3E1E11CB9_H__

#include "Modules/IEmotionModule.h"
#include "EmoCfgParseTool.h"

class EmotionDialog;
class EmotionModule_Impl final : public module::IEmotionModule {
public:
    EmotionModule_Impl();
    virtual ~EmotionModule_Impl();

public:
	virtual void showEmotionDialog(IN std::string sid,IN POINT pt);
	virtual BOOL getEmotionNameByID(IN CString ID, OUT CString& csPath);
	virtual BOOL getEmotionIDByName(IN CString csName, OUT CString& csID);
	virtual std::string  getCurEmotionWndSessionId(void);

	virtual void getAllEmotionFileNames(OUT std::list<CString>& nameList);

private:
	EmotionDialog*				m_emotionWindow;//指向 EmotionDialog 对象的指针，用于显示表情窗口
	std::string					m_sid;			//当前显示窗口的会话ID
	EmoCfgParseTool*			m_pEmotionKey;	//指向 EmoCfgParseTool 对象的指针，用于解析表情配置文件
};

#endif// EMOTIONMODULE_IMPL_9432EBF5_DD5E_4C01_BF4B_A8D3E1E11CB9_H__
