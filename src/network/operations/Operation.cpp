
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 封装的操作对象operation
*/

#include "GlobalConfig.h"
#include "yaolog/yaolog.h"
#include "network/Exception.h"
#include "network/Operation.h"

NAMESPACE_BEGIN(imcore)

const std::string OPERATION_NAME_COMMON = "operation_name_common";

Operation::Operation()
:m_state(OPERATION_IDLE)
, m_name(OPERATION_NAME_COMMON)
{

}

Operation::Operation(const std::string& name)
:m_state(OPERATION_IDLE)
,m_name(name)
{

}

Operation::~Operation()
{

}

void Operation::process()
{
	try
	{
		m_state = OPERATION_RUNNING;
		processOpertion();
	}
	catch (Exception& exc)
	{
		assert(false);
		LOG__(ERR, _T("process exception,reason:%s"),exc.what());
	}
	catch (std::exception& exc)
	{
		assert(false);
		LOG__(ERR, _T("process exception,reason:%s"), exc.what());
	}
	catch (...)
	{
		assert(false);
		LOG__(ERR, _T("process unknown exception"));
	}
	m_state = OPERATION_FINISHED;
}

void Operation::release()
{
	delete this;
}

NAMESPACE_END(imcore)
