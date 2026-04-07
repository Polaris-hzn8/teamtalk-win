
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef _CALLBACK_OPERATION_EVENT_H_
#define _CALLBACK_OPERATION_EVENT_H_

#include <memory>
#include <functional>
#include <global_define.h>
#include <modules/Base/IEvent.h>
#include <utility/utilCommonAPI.h>

NAMESPACE_BEGIN(module)

// 回调函数类型
typedef std::function<void(std::shared_ptr<void>)> IOperationDelegate;

// 回调函数委托 类型别名
//template<typename T>
//using IOperationDelegate = std::function<void(std::shared_ptr<T>)>;

// 异步回调事件
class ICallbackOperationEvent : public module::IEvent
{
public:
	ICallbackOperationEvent(IOperationDelegate& callback, std::shared_ptr<void> param)
		:m_callback(callback), m_param(param) {}
	virtual ~ICallbackOperationEvent() {}
	virtual void process() { m_callback(m_param); }
	virtual void release() { delete this; }
private:
	IOperationDelegate		m_callback;
	std::shared_ptr<void>	m_param;
};

NAMESPACE_END(module)

#endif// _CALLBACK_OPERATION_EVENT_H_
