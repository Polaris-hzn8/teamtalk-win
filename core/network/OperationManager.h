
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef OPERATIONMANAGER_7EEF3272_2557_4A76_9C25_67D4639F40DB_H__
#define OPERATIONMANAGER_7EEF3272_2557_4A76_9C25_67D4639F40DB_H__

#include <list>
#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>
#include "network/ErrorCode.h"

NAMESPACE_BEGIN(imcore)

class Operation;

class OperationManager
{
public:
	OperationManager() = default;
	~OperationManager();
	OperationManager(OperationManager&) = delete;
	OperationManager(OperationManager&&) = delete;
	OperationManager& operator= (OperationManager&) = delete;
	OperationManager& operator= (OperationManager&&) = delete;
public:
	IMCoreErrorCode startup();
    void shutdown(IN int seconds = 2000);
    IMCoreErrorCode startOperation(IN Operation* pOperation, Int32 delay);
    IMCoreErrorCode startOperationWithLambda(std::function<void()> operationRun
        , Int32 delay
        , std::string oper_name);
    IMCoreErrorCode clearOperationByName(std::string oper_name);

private:
	std::list<Operation*>      m_vecDelayOperations;
	std::list<Operation*>      m_vecRealtimeOperations;

	std::mutex					m_cvMutex;	// 互斥锁
	std::condition_variable		m_CV;		// 条件变量

	std::mutex					m_mutexOperation;
	bool                        m_bContinue = true;
	std::thread					m_operationThread;
};

OperationManager* getOperationManager();

NAMESPACE_END(imcore)

#endif// OPERATIONMANAGER_7EEF3272_2557_4A76_9C25_67D4639F40DB_H__
