/*******************************************************************************
 *  @file      IEmotionModule.h 2014\8\6 20:03:22 $
 *  @author    快刀<kuaidao@mogujie.com>
 *  @brief     表情管理模块
 ******************************************************************************/

#ifndef IEMOTIONMODULE_8E431B43_8F05_4934_8B5B_BB839730F3A6_H__
#define IEMOTIONMODULE_8E431B43_8F05_4934_8B5B_BB839730F3A6_H__

/*
	这是一个名为"IEmotionModule.h"的头文件 文件中包含了一些宏定义、常量和类的声明
	该头文件主要定义了表情管理模块的接口 interface（以纯虚函数实现） 负责管理和处理表情相关的功能
	具体的实现应该在继承该接口的具体类中进行 实现在EmotionModule_Impl.h .cpp中实现
*/

#include "GlobalDefine.h"
#include "Modules/ModuleDll.h"
#include "Modules/ModuleBase.h"

//NAMESPACE_BEGIN(module) 和 NAMESPACE_END(module) 定义了一个命名空间，其中包含了模块相关的内容。
NAMESPACE_BEGIN(module)


const std::string MODULE_EMOTION_PREFIX = "Emotion";//表情前缀
const std::string KEY_EMOTION_SELECTED = MODULE_EMOTION_PREFIX + "selected";//选择了某个表情 KEYID

/**
 * The class 表情管理模块
 */

class EmotionParam {
public:
	std::string			 sid;
	CString				 strPath;
};

/*
	MODULE_API 是一个宏定义，用于导出模块的接口
	IEmotionModule 是一个抽象类，继承自module::ModuleBase，用于定义表情管理模块的接口
	该接口包括了一些纯虚函数 如:
	  showEmotionDialog 用于显示表情窗口
	  getEmotionNameByID 用于根据表情ID获取表情名称
	  getEmotionIDByName 用于根据表情名称获取表情ID等
*/ 
class MODULE_API IEmotionModule : public module::ModuleBase {
public:
	/**
	 * 显示表情窗口
	 * @param   POINT pt 显示的位置
	 * @return  void
	 * @exception there is no any exception to throw.
	 */
	virtual void showEmotionDialog(IN std::string sid, IN POINT pt) = 0;
	virtual BOOL getEmotionNameByID(IN CString ID, OUT CString& csPath) = 0;
	virtual BOOL getEmotionIDByName(IN CString csPath, OUT CString& ID) = 0;

	/**
	* 获取当前显示窗口的会话ID
	* @param   POINT pt 显示的位置
	* @return  void
	* @exception there is no any exception to throw.
	*/
	virtual std::string  getCurEmotionWndSessionId(void) = 0;

	/**
	 * 获取所有表情文件的文件名列表
	 * 调用该函数时，表情管理模块应该将所有的表情文件名添加到 nameList 列表中，以便调用者可以获取到所有的表情文件名
	 * 由于这是一个纯虚函数（函数后面的 = 0 表示纯虚函数），在接口中只有函数声明而没有具体的实现。具体的实现应该在继承该接口的具体类中进行
	 * @nameList   一个输出参数 是一个std::list<CString>类型的引用 表示用于存储表情文件名的列表
	 * @return  void
	 */
	virtual void getAllEmotionFileNames(OUT std::list<CString>& nameList) = 0;
};

// getEmotionModule 是一个函数，用于获取表情管理模块的实例
MODULE_API IEmotionModule* getEmotionModule();


NAMESPACE_END(module)


#endif// IEMOTIONMODULE_8E431B43_8F05_4934_8B5B_BB839730F3A6_H__


