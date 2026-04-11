
#ifndef _CREF_OBJECT_H_
#define _CREF_OBJECT_H_

#include <atomic>
#include <string>
#include <imcore/ostype.h>

namespace imcore {

// 引用计数对象类
class NETWORK_DLL CRefObject {
 public:
  CRefObject();
  virtual ~CRefObject();

  void AddRef();
  void ReleaseRef();

 private:
  std::atomic<int> m_refCount;
};

}  // namespace imcore

#endif  // _CREF_OBJECT_H_
