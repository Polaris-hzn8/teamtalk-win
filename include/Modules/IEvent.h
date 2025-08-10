
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef IEVENT_83A4713C_930E_426A_98F5_8BB8747994D3_H__
#define IEVENT_83A4713C_930E_426A_98F5_8BB8747994D3_H__

#include "GlobalDefine.h"
#include "utility/utilCommonAPI.h"

namespace imcore
{
	struct Exception;
}

NAMESPACE_BEGIN(module)

struct IEvent
{
public:
	virtual void process() = 0;
	virtual void onException(imcore::Exception* e)
	{
		LOG__(ERR, _T("IEvent exception,%d"));
		assert(FALSE);
	}
	virtual void release() = 0;
};

struct ITimerEvent : public IEvent
{};

NAMESPACE_END(module)

#endif// IEVENT_83A4713C_930E_426A_98F5_8BB8747994D3_H__
