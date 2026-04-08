
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef UTILAPI_AF8EB6AC_116D_4D74_8AFA_0C5E7BF6FFEB_H__
#define UTILAPI_AF8EB6AC_116D_4D74_8AFA_0C5E7BF6FFEB_H__

#include "stdafx.h"
#include <list>
#include <mutex>
#include <string>
#include <global_define.h>
#include <utility/utility_dll.h>

NAMESPACE_BEGIN(util)

// APP相关
UTILITY_API CString getAppPath();
UTILITY_API CString getParentAppPath();

// APP文件相关
UTILITY_API BOOL createAllDirectories(CString& csDir);
UTILITY_API std::string getHumanReadableSizeString(double size);
UTILITY_API BOOL isFileExist(IN const LPCTSTR csFileName);

// hash函数
UTILITY_API UInt32 hash_BKDR(const char* str);
UTILITY_API void messagePump();
UTILITY_API CString getMd5CString(const char* pSrc, size_t length);
UTILITY_API BOOL registerDll(const CString& sFilePath);
UTILITY_API BOOL waitSingleObject(HANDLE handle, Int32 timeout);

// 时间和延时
UTILITY_API uint64_t get_tick_count();
UTILITY_API void util_sleep(uint32_t millisecond);

// 文件操作
UTILITY_API size_t get_file_size(const char* path);

// 网络IP转换
UTILITY_API unsigned int ip2long(const char* ip);
UTILITY_API char* long2ip(const unsigned int in);

// 进程相关
UTILITY_API void writePid();

NAMESPACE_END(util)

#endif  // UTILAPI_af8eb6ac-116d-4d74-8afa-0c5e7bf6ffeb_H__
