
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 
	ICallbackOpertaion
	1.module::ICallbackOperation 继承自 imcore::Operation		-> module依赖imcore的执行单元
	2.IPduPacketParse::onPacket 需要 imcore::TTPBHeader		-> module依赖imcore的网络层协议
	3.核心层(imcore) + 扩展层(module) 双向依赖接口设计
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

// 异步操作接口
class MODULE_CLASS ICallbackOpertaion : public imcore::Operation
{
public:
	ICallbackOpertaion(IOperationDelegate& callback):m_callback(callback) {}
	virtual ~ICallbackOpertaion() {}
protected:
	void syncCallback(std::shared_ptr<void> param) { m_callback(param); }	// 同步回调
	void asyncCallback(std::shared_ptr<void> param)							// 异步回调 借助UIEvent
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
	virtual void onPacket(imcore::TTPBHeader& header, std::string& pbBody) = 0; //TCP网络包解析
};

NAMESPACE_END(module)

#endif// IMODULEINTERFACE_26428d8b-4585-4660-95b3-94e8735700e9_H__
