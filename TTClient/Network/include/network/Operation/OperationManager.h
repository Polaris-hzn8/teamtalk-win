
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 异步操作管理器
        用于管理和调度异步任务 执行延时或实时任务
*/

#ifndef OPERATIONMANAGER_7EEF3272_2557_4A76_9C25_67D4639F40DB_H__
#define OPERATIONMANAGER_7EEF3272_2557_4A76_9C25_67D4639F40DB_H__

#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <mutex>
#include <network/operation/ErrorCode.h>
#include <string>
#include <thread>

namespace network {

/**
 * @brief OperationManager 异步任务管理器
 * 支持延迟执行和实时执行的任务调度
 * 内部维护独立工作线程，通过条件变量唤醒
 * 特点：
 *  - 单例访问（getOperationManager）
 *  - 线程安全
 *  - 支持延迟任务和 lambda 任务
 */
class Operation;
class OperationManager {
 public:
  OperationManager() = default;
  ~OperationManager();
  // 禁止拷贝与移动
  OperationManager(OperationManager&) = delete;
  OperationManager(OperationManager&&) = delete;
  OperationManager& operator=(OperationManager&) = delete;
  OperationManager& operator=(OperationManager&&) = delete;

 public:
  IMCoreErrorCode startup();
  void shutdown(IN int seconds = 2000);
  IMCoreErrorCode startOperation(IN Operation* pOperation, Int32 delay);
  IMCoreErrorCode startOperationWithLambda(std::function<void()> operationRun, Int32 delay, std::string oper_name);
  IMCoreErrorCode clearOperationByName(std::string oper_name);

 private:
  std::list<Operation*> m_vecDelayOperations;
  std::list<Operation*> m_vecRealtimeOperations;

  std::mutex m_cvMutex;          // 互斥锁
  std::condition_variable m_cv;  // 条件变量

  std::mutex m_mutexOperation;
  std::atomic_bool m_bContinue{true};  // 运行标志（线程安全）
  std::thread m_operationThread;
};

OperationManager* getOperationManager();

}  // namespace network

#endif  // OPERATIONMANAGER_7EEF3272_2557_4A76_9C25_67D4639F40DB_H__
