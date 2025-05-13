
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef IMODULEINTERFACE_26428D8B_4585_4660_95B3_94E8735700E9_H__
#define IMODULEINTERFACE_26428D8B_4585_4660_95B3_94E8735700E9_H__

#include <string>
#include <functional>
#include "GlobalDefine.h"
#include "Modules/IEvent.h"
#include "network/Operation.h"
#include "Modules/ModuleDll.h"
#include "Modules/UIEventManager.h"

namespace imcore
{
	class TTPBHeader;
}

NAMESPACE_BEGIN(module)

typedef std::function<void(std::shared_ptr<void>)> IOperationDelegate;

// 操作回调事件，主要用于在任务执行过程中通知回调
class CallbackOperationEvent : public module::IEvent
{
public:
	CallbackOperationEvent(IOperationDelegate& callback, std::shared_ptr<void> param)
		:m_callback(callback)
		, m_param(param)
	{

	}
	virtual ~CallbackOperationEvent() {}
	virtual void process()
	{
		m_callback(m_param);
	}
	virtual void release() { delete this; }
private:
	IOperationDelegate				m_callback;
	std::shared_ptr<void>			m_param;
};

// 具有通知回调的异步操作
class MODULE_CLASS ICallbackOpertaion : public imcore::Operation
{
public:
	ICallbackOpertaion(IOperationDelegate& callback)
		:m_callback(callback)
	{
	}
	virtual ~ICallbackOpertaion() {}
protected:
	/**
	 * \brief 同步回调
	 * \param std::shared_ptr<void>
	 * \param param
	 */
	void syncCallback(std::shared_ptr<void> param)
	{
		m_callback(param);
	}
	/**
	 * \brief 异步回调，借助UIEvent
	 * \param param std::shared_ptr<void>
	 */
	void asyncCallback(std::shared_ptr<void> param)
	{
		CallbackOperationEvent* pEvent = new CallbackOperationEvent(m_callback, param);
		module::getEventManager()->asynFireUIEvent(pEvent);
	}
private:
	IOperationDelegate m_callback;
};

// IPduPacketParse
struct IPduPacketParse
{
public:
	/**
	 * \brief 收到TcpClient网络包后的包解析回调接口
	 * \param header std::auto_ptr<CImPdu> pdu
	 * \param pbBody
	 */
	virtual void onPacket(imcore::TTPBHeader& header, std::string& pbBody) = 0;
};

NAMESPACE_END(module)

#endif// IMODULEINTERFACE_26428d8b-4585-4660-95b3-94e8735700e9_H__
