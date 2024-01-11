/*******************************************************************************
 *  @file      EmotionModule_Impl.h 2014\8\6 20:05:39 $
 *  @author    �쵶<kuaidao@mogujie.com>
 *  @brief     
 ******************************************************************************/

#ifndef EMOTIONMODULE_IMPL_9432EBF5_DD5E_4C01_BF4B_A8D3E1E11CB9_H__
#define EMOTIONMODULE_IMPL_9432EBF5_DD5E_4C01_BF4B_A8D3E1E11CB9_H__

#include "Modules/IEmotionModule.h"
#include "EmoCfgParseTool.h"

class EmotionDialog;

/*
	���ļ�������һ����Ϊ EmotionModule_Impl ���࣬����̳��� IEmotionModule �ӿڣ����麯����ʵ���˾���ı������ģ��Ĺ���
	���еĳ�Ա����ʵ���� IEmotionModule �ӿ��������ĺ���������
	  showEmotionDialog
	  getEmotionNameByID
	  getEmotionIDByName
	  getCurEmotionWndSessionId
	  getAllEmotionFileNames
	  ��Щ�����ľ���ʵ�ֻ����ʵ�����������
*/
class EmotionModule_Impl final : public module::IEmotionModule {
public:
	//���캯��
    EmotionModule_Impl();
	//����������
    virtual ~EmotionModule_Impl();

public:
	virtual void showEmotionDialog(IN std::string sid,IN POINT pt);
	virtual BOOL getEmotionNameByID(IN CString ID, OUT CString& csPath);
	virtual BOOL getEmotionIDByName(IN CString csName, OUT CString& csID);
	virtual std::string  getCurEmotionWndSessionId(void);

	virtual void getAllEmotionFileNames(OUT std::list<CString>& nameList);

private:
	EmotionDialog*				m_emotionWindow;//ָ�� EmotionDialog �����ָ�룬������ʾ���鴰��
	std::string					m_sid;			//��ǰ��ʾ���ڵĻỰID
	EmoCfgParseTool*			m_pEmotionKey;	//ָ�� EmoCfgParseTool �����ָ�룬���ڽ������������ļ�
};

#endif// EMOTIONMODULE_IMPL_9432EBF5_DD5E_4C01_BF4B_A8D3E1E11CB9_H__
