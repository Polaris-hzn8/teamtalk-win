

#include <network/utils/CRefObject.h>

namespace network {

// CRefObject实现
CRefObject::CRefObject() {
  m_lock = nullptr;
  m_refCount = 1;
}

CRefObject::~CRefObject() {}

void CRefObject::AddRef() {
  if (m_lock) {
    m_lock->lock();
    m_refCount++;
    m_lock->unlock();
  } else {
    m_refCount++;
  }
}

void CRefObject::ReleaseRef() {
  if (m_lock) {
    m_lock->lock();
    m_refCount--;
    if (m_refCount == 0) {
      delete this;
      return;
    }
    m_lock->unlock();
  } else {
    m_refCount--;
    if (m_refCount == 0)
      delete this;
  }
}

}  // namespace network