// OS dependant type definition
#ifndef __OS_TYPE_H__
#define __OS_TYPE_H__

#ifdef _MSC_VER
#include <WinBase.h>
#include <WinSock2.h>
#include <Windows.h>
#include <direct.h>
#include <stdint.h>
#else
#ifdef __APPLE__
#include <sys/event.h>
#include <sys/syscall.h>  // syscall(SYS_gettid)
#include <sys/time.h>
#else
#include <sys/epoll.h>
#endif
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>  // define int8_t ...
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define closesocket close
#define ioctlsocket ioctl
#endif
#include <stdexcept>

#ifdef _MSC_VER
// typedef char			int8_t;
// typedef short			int16_t;
// typedef int				int32_t;
// typedef	long long		int64_t;
// typedef unsigned char	uint8_t;
// typedef unsigned short	uint16_t;
// typedef unsigned int	uint32_t;
// typedef	unsigned long long	uint64_t;
typedef int socklen_t;
#else
typedef int SOCKET;
typedef int BOOL;
const int TRUE = 1;
const int FALSE = 0;
const int SOCKET_ERROR = -1;
const int INVALID_SOCKET = -1;
#endif

typedef unsigned char uchar_t;
typedef int net_handle_t;
typedef int conn_handle_t;

enum { NETLIB_OK = 0, NETLIB_ERROR = -1 };

#define NETLIB_INVALID_HANDLE -1

enum {
  NETLIB_MSG_CONNECT = 1,
  NETLIB_MSG_CONFIRM,
  NETLIB_MSG_READ,
  NETLIB_MSG_WRITE,
  NETLIB_MSG_CLOSE,
  NETLIB_MSG_TIMER,
  NETLIB_MSG_LOOP,
};

typedef void (*callback_t)(void* callback_data, uint8_t msg, uint32_t handle, void* pParam);

#ifdef WIN32
#ifdef NETWORK_EXPORTS
#define NETWORK_DLL __declspec(dllexport)
#else
#define NETWORK_DLL __declspec(dllimport)
#endif
#else
#define NETWORK_DLL
#endif

#endif
