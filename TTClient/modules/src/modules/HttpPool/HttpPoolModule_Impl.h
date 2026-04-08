
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: HTTP操作线程池
*/

#ifndef HTTPPOOLMODULE_IMPL_43FDB575_36B4_4CFC_B205_89A9D1904A4C_H__
#define HTTPPOOLMODULE_IMPL_43FDB575_36B4_4CFC_B205_89A9D1904A4C_H__

#include <list>
#include <modules/IHttpPoolModule.h>
#include <network/basic/lock.h>
#include <utility/TTThread.h>
#include <vector>

class HttpPoolModule_Impl;
class TTHttpThread : public util::TTThread {
 public:
  explicit TTHttpThread(HttpPoolModule_Impl* owner);
  virtual ~TTHttpThread();

  void requestExit() { m_bContinue = FALSE; }
  bool waitForExit(DWORD dwWaitTime) { return wait(dwWaitTime) ? true : false; }

 private:
  virtual UInt32 process() override;

  BOOL m_bContinue;
  HttpPoolModule_Impl* m_Owner;
};

class HttpPoolModule_Impl final : public module::IHttpPoolModule {
  friend class TTHttpThread;

 public:
  HttpPoolModule_Impl();
  virtual ~HttpPoolModule_Impl();

  virtual void pushHttpOperation(module::IHttpOperation* pOperaion, BOOL bHighPriority = FALSE);
  virtual void shutdown();

 private:
  BOOL _launchThread();         // 线程管理
  void _cancelAllOperations();  // 取消所有操作

  std::list<module::IHttpOperation*> m_lstHttpOpers;  // http操作队列
  std::vector<TTHttpThread*> m_vecHttpThread;         // http线程池
  HANDLE m_hSemaphore;
  CLock m_mtxLock;

  int m_maxThreadCount;       // 线程池最大线程数
  volatile BOOL m_bShutdown;  // 是否关闭
};

#endif  // HTTPPOOLMODULE_IMPL_43fdb575-36b4-4cfc-b205-89a9d1904a4c_H__
