/*******************************************************************************
 *  @file      EmotionModule_Impl.h 2014\8\6 20:05:39 $
 *  @author    快刀<kuaidao@mogujie.com>
 *  @brief     
 ******************************************************************************/

#ifndef EMOTIONMODULE_IMPL_9432EBF5_DD5E_4C01_BF4B_A8D3E1E11CB9_H__
#define EMOTIONMODULE_IMPL_9432EBF5_DD5E_4C01_BF4B_A8D3E1E11CB9_H__

#include "Modules/IEmotionModule.h"
#include "EmoCfgParseTool.h"

class EmotionDialog;

/*
	该文件定义了一个名为 EmotionModule_Impl 的类，该类继承自 IEmotionModule 接口（纯虚函数）实现了具体的表情管理模块的功能
	类中的成员函数实现了 IEmotionModule 接口中声明的函数，包括
	  showEmotionDialog
	  getEmotionNameByID
	  getEmotionIDByName
	  getCurEmotionWndSessionId
	  getAllEmotionFileNames
	  这些函数的具体实现会根据实际需求来完成
*/
class EmotionModule_Impl final : public module::IEmotionModule {
public:
	//构造函数
    EmotionModule_Impl();
	//虚析构函数
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
