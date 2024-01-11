/*******************************************************************************
 *  @file      IEmotionModule.h 2014\8\6 20:03:22 $
 *  @author    �쵶<kuaidao@mogujie.com>
 *  @brief     �������ģ��
 ******************************************************************************/

#ifndef IEMOTIONMODULE_8E431B43_8F05_4934_8B5B_BB839730F3A6_H__
#define IEMOTIONMODULE_8E431B43_8F05_4934_8B5B_BB839730F3A6_H__

/*
	����һ����Ϊ"IEmotionModule.h"��ͷ�ļ� �ļ��а�����һЩ�궨�塢�������������
	��ͷ�ļ���Ҫ�����˱������ģ��Ľӿ� interface���Դ��麯��ʵ�֣� �������ʹ��������صĹ���
	�����ʵ��Ӧ���ڼ̳иýӿڵľ������н��� ʵ����EmotionModule_Impl.h .cpp��ʵ��
*/

#include "GlobalDefine.h"
#include "Modules/ModuleDll.h"
#include "Modules/ModuleBase.h"

//NAMESPACE_BEGIN(module) �� NAMESPACE_END(module) ������һ�������ռ䣬���а�����ģ����ص����ݡ�
NAMESPACE_BEGIN(module)


const std::string MODULE_EMOTION_PREFIX = "Emotion";//����ǰ׺
const std::string KEY_EMOTION_SELECTED = MODULE_EMOTION_PREFIX + "selected";//ѡ����ĳ������ KEYID

/**
 * The class �������ģ��
 */

class EmotionParam {
public:
	std::string			 sid;
	CString				 strPath;
};

/*
	MODULE_API ��һ���궨�壬���ڵ���ģ��Ľӿ�
	IEmotionModule ��һ�������࣬�̳���module::ModuleBase�����ڶ���������ģ��Ľӿ�
	�ýӿڰ�����һЩ���麯�� ��:
	  showEmotionDialog ������ʾ���鴰��
	  getEmotionNameByID ���ڸ��ݱ���ID��ȡ��������
	  getEmotionIDByName ���ڸ��ݱ������ƻ�ȡ����ID��
*/ 
class MODULE_API IEmotionModule : public module::ModuleBase {
public:
	/**
	 * ��ʾ���鴰��
	 * @param   POINT pt ��ʾ��λ��
	 * @return  void
	 * @exception there is no any exception to throw.
	 */
	virtual void showEmotionDialog(IN std::string sid, IN POINT pt) = 0;
	virtual BOOL getEmotionNameByID(IN CString ID, OUT CString& csPath) = 0;
	virtual BOOL getEmotionIDByName(IN CString csPath, OUT CString& ID) = 0;

	/**
	* ��ȡ��ǰ��ʾ���ڵĻỰID
	* @param   POINT pt ��ʾ��λ��
	* @return  void
	* @exception there is no any exception to throw.
	*/
	virtual std::string  getCurEmotionWndSessionId(void) = 0;

	/**
	 * ��ȡ���б����ļ����ļ����б�
	 * ���øú���ʱ���������ģ��Ӧ�ý����еı����ļ�����ӵ� nameList �б��У��Ա�����߿��Ի�ȡ�����еı����ļ���
	 * ��������һ�����麯������������� = 0 ��ʾ���麯�������ڽӿ���ֻ�к���������û�о����ʵ�֡������ʵ��Ӧ���ڼ̳иýӿڵľ������н���
	 * @nameList   һ��������� ��һ��std::list<CString>���͵����� ��ʾ���ڴ洢�����ļ������б�
	 * @return  void
	 */
	virtual void getAllEmotionFileNames(OUT std::list<CString>& nameList) = 0;
};

// getEmotionModule ��һ�����������ڻ�ȡ�������ģ���ʵ��
MODULE_API IEmotionModule* getEmotionModule();


NAMESPACE_END(module)


#endif// IEMOTIONMODULE_8E431B43_8F05_4934_8B5B_BB839730F3A6_H__


