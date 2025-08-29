
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 
	ICallbackOpertaion
	1.module::ICallbackOperation �̳��� imcore::Operation		-> module����imcore��ִ�е�Ԫ
	2.IPduPacketParse::onPacket ��Ҫ imcore::TTPBHeader		-> module����imcore�������Э��
	3.���Ĳ�(imcore) + ��չ��(module) ˫�������ӿ����
*/

#ifndef IMODULEINTERFACE_26428D8B_4585_4660_95B3_94E8735700E9_H__
#define IMODULEINTERFACE_26428D8B_4585_4660_95B3_94E8735700E9_H__

#include <string>
#include <functional>
#include "GlobalDefine.h"
#include "Modules/IEvent.h"
#include "Modules/ModuleDll.h"
#include "Modules/UIEventManager.h"
#include "Modules/ICallbackOperationEvent.h"
#include "network/Operation.h"

namespace imcore
{
	class TTPBHeader;
}

NAMESPACE_BEGIN(module)

// �첽�����ӿ�
class MODULE_CLASS ICallbackOpertaion : public imcore::Operation
{
public:
	ICallbackOpertaion(IOperationDelegate& callback):m_callback(callback) {}
	virtual ~ICallbackOpertaion() {}
protected:
	void syncCallback(std::shared_ptr<void> param) { m_callback(param); }	// ͬ���ص�
	void asyncCallback(std::shared_ptr<void> param)							// �첽�ص� ����UIEvent
	{
		ICallbackOperationEvent* pEvent = new ICallbackOperationEvent(m_callback, param);
		module::getEventManager()->asynFireUIEvent(pEvent);
	}
private:
	IOperationDelegate m_callback;
};

struct IPduPacketParse
{
public:
	virtual void onPacket(imcore::TTPBHeader& header, std::string& pbBody) = 0; //TCP���������
};

NAMESPACE_END(module)

#endif// IMODULEINTERFACE_26428d8b-4585-4660-95b3-94e8735700e9_H__
