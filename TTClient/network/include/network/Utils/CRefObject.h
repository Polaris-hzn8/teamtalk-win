
#ifndef _CREF_OBJECT_H_
#define _CREF_OBJECT_H_

#include <mutex>
#include <string>
#include <network/ostype.h>

namespace network {

// 引用计数对象类
class NETWORK_DLL CRefObject {
 public:
  CRefObject();
  virtual ~CRefObject();

  void SetLock(std::mutex* lock) { m_lock = lock; }
  void AddRef();
  void ReleaseRef();

 private:
  int m_refCount;
  std::mutex* m_lock;
};

} // namespace network

#endif // _CREF_OBJECT_H_
