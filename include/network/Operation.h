
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 封装的操作对象operation
*/

#ifndef OPERATION_D8F2BC78_108D_4219_9D6E_F1728D1B8C95_H__
#define OPERATION_D8F2BC78_108D_4219_9D6E_F1728D1B8C95_H__

#include "IOperation.h"
#include "GlobalDefine.h"
#include "network/networkdll.h"

NAMESPACE_BEGIN(imcore)

class NETWORK_DLL Operation : public IOperation
{
	enum OperationState
	{
		OPERATION_IDLE = 0,
		OPERATION_STARTING,
		OPERATION_RUNNING,
		OPERATION_CANCELLING,
		OPERATION_FINISHED
	};

public:
    Operation();
	Operation(const std::string& name);
    virtual ~Operation();

public:
	virtual void processOpertion() = 0;

public:
	virtual void process();
	virtual void release();

    inline std::string name() const { return m_name; }
    inline void set_name(__in std::string name){ m_name = name; }

private:
	OperationState			m_state;
    std::string				m_name;
};

NAMESPACE_END(imcore)

#endif// OPERATION_D8F2BC78_108D_4219_9D6E_F1728D1B8C95_H__
