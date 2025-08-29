
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef OBSERVER_6444A026_CF7D_4675_BD86_A112B52B992D_H__
#define OBSERVER_6444A026_CF7D_4675_BD86_A112B52B992D_H__

#include <tuple>
#include <memory>
#include <functional>
#include "GlobalDefine.h"
#include "Modules/IEvent.h"
#include "Modules/IMKOEvent.h"

enum
{
	MKO_STRING = 0,
	MKO_INT,
	MKO_SHARED_VOIDPTR,
	MKO_VOIDPTR,
};

typedef std::tuple<std::string, Int32, std::shared_ptr<void>, void*> MKO_TUPLE_PARAM;
typedef std::function<void(std::string, MKO_TUPLE_PARAM)> MKODelegate;

#define BIND_CALLBACK_1(func)   std::bind(&func, this, placeholders::_1)
#define BIND_CALLBACK_2(func)	std::bind(&func, this, placeholders::_1, placeholders::_2)

NAMESPACE_BEGIN(module)
class ModuleSubject;
class ModuleObserverCtx;

class MKOEvent_Impl final : public IMKOEvent
{
public:
	MKOEvent_Impl(IN ModuleSubject* p);
	virtual ~MKOEvent_Impl();
public:
	virtual void process();
	virtual void release();

public:
	std::string						m_keyId;

	Int32							m_mkoInt;
	void*							m_pmkoVoid;
	std::string						m_mkoString;
	std::shared_ptr<void>			m_pmkoShardVoid;

	ModuleSubject*					m_pMko;        //为了调用ModuleSubject的接口，这里放一个映射指针
};

class ModuleObserverCtx
{
public:
	ModuleObserverCtx(MKODelegate& hd, void* pObserObject);

public:
	std::string				keyId;
	void*					m_pObserverObject;
	MKODelegate				callback;
};

NAMESPACE_END(module)

#endif// OBSERVER_6444a026-cf7d-4675-bd86-a112b52b992d_H__
