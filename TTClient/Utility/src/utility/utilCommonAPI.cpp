
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#include "stdafx.h"
#include <shellapi.h>
#include <shlwapi.h>
#include <sys/stat.h>

#include <libsecurity/sk_md5.h>
#include <utility/TTThread.h>
#include <utility/utilCommonAPI.h>

#ifdef _MSC_VER
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

NAMESPACE_BEGIN(util)

CString binToHexToCString(const unsigned char* data, size_t len) {
  TCHAR* Hex = (TCHAR*)_T("0123456789abcdef");
  std::wstring hex;
  hex.resize(len << 1);

  for (size_t i = 0; i < len; i++) {
    UINT b = (UINT)data[i];
    hex[i * 2] = Hex[b >> 4];
    hex[i * 2 + 1] = Hex[b & 0xF];
  }

  return hex.c_str();
}

void getMd5CString(const char* pSrc, size_t length, std::vector<unsigned char>& res) {
  res.clear();
  res.resize(16);
  md5_ctxt ctx;
  md5_init(&ctx);
  md5_loop(&ctx, (BYTE*)pSrc, length);
  md5_pad(&ctx);
  md5_result(&res[0], &ctx);
}

CString getMd5CString(const char* pSrc, size_t length) {
  std::vector<unsigned char> bmd5;
  getMd5CString(pSrc, length, bmd5);

  return binToHexToCString(&bmd5[0], 16);
}  // 避免重复计算

// 避免重复计算
CString getAppPath() {
  static CString sAppPath = _T("");
  if (sAppPath.IsEmpty()) {
    TCHAR buffer[MAX_PATH];
    ZeroMemory(buffer, sizeof(TCHAR) * MAX_PATH);

    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule) {
      GetModuleFileName(hModule, buffer, MAX_PATH);
      PathRemoveFileSpec(buffer);
      sAppPath = buffer;
      sAppPath += _T("\\");
    }
  }
  return sAppPath;
}

CString getParentAppPath() {
  static CString sParentAppPath = _T("");
  if (sParentAppPath.IsEmpty()) {
    sParentAppPath = getAppPath();
    LPTSTR lpszPath = sParentAppPath.GetBuffer();
    PathRemoveBackslash(lpszPath);
    PathRemoveFileSpec(lpszPath);
    sParentAppPath = lpszPath;
    sParentAppPath += _T("\\");
  }
  return sParentAppPath;
}

BOOL createAllDirectories(CString& csDir) {
  if (csDir.Right(1) == _T("\\")) {
    csDir = csDir.Left(csDir.GetLength() - 1);
  }

  if (GetFileAttributes(csDir) != INVALID_FILE_ATTRIBUTES) {
    return TRUE;
  }

  int nFound = csDir.ReverseFind('\\');
  createAllDirectories(csDir.Left(nFound));

  if (!::CreateDirectory(csDir, NULL)) {
    return FALSE;
  }

  return TRUE;
}

UInt32 hash_BKDR(const char* str) {
  unsigned int seed = 131;  // 31 131 1313 13131 131313 etc.
  unsigned int hash = 0;
  while (*str) {
    hash = hash * seed + (*str++);
  }
  return (hash & 0x7FFFFFFF);
}

void messagePump() {
  MSG msg;
  while (::GetMessage(&msg, NULL, 0, 0) > 0) {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }
}

std::string getHumanReadableSizeString(double size) {
  // const TCHAR* units[] = { _T("B"), _T("KB"), _T("MB"), _T("GB"), _T("TB"), _T("PB"), _T("EB"), _T("ZB"), _T("YB")
  // };
  const char* units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
  int i = 0;
  while (size > 1024) {
    size /= 1024;
    i++;
  }
  char buf[1024];
  sprintf_s(buf, 1024, "%.*f %s", i, size, units[i]);
  return std::string(buf);
}

BOOL isFileExist(IN const LPCTSTR csFileName) {
  PTR_FALSE(csFileName);
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind;

  hFind = FindFirstFile(csFileName, &FindFileData);
  if (hFind != INVALID_HANDLE_VALUE) {
    FindClose(hFind);
    return TRUE;
  }
  return FALSE;
}

BOOL registerDll(const CString& sFilePath) {
  if (!PathFileExists(sFilePath))
    return FALSE;

  typedef LRESULT (*DllRegisterServerProc)(void);
  BOOL retVal = FALSE;
  HINSTANCE hDll = LoadLibrary(sFilePath);
  while (TRUE) {
    if (hDll == NULL)
      break;
    DllRegisterServerProc DllRegisterServer;
    DllRegisterServer = (DllRegisterServerProc)GetProcAddress(hDll, "DllRegisterServer");
    if (DllRegisterServer == NULL)
      break;

    int temp = DllRegisterServer();
    if (temp != S_OK)
      break;

    retVal = TRUE;
    break;
  }

  FreeLibrary(hDll);
  return retVal;
}

BOOL waitSingleObject(HANDLE handle, Int32 timeout) {
  int t = 0;
  DWORD waitResult = WAIT_FAILED;
  do {
    int timeWaiter = 500;
    t += timeWaiter;
    waitResult = WaitForSingleObject(handle, timeWaiter);
  } while ((WAIT_TIMEOUT == waitResult) && (t < timeout));

  return (WAIT_OBJECT_0 == waitResult);
}

uint64_t get_tick_count() {
#ifdef _MSC_VER
  LARGE_INTEGER liCounter;
  LARGE_INTEGER liCurrent;

  if (!QueryPerformanceFrequency(&liCounter))
    return GetTickCount();

  QueryPerformanceCounter(&liCurrent);
  return (uint64_t)(liCurrent.QuadPart * 1000 / liCounter.QuadPart);
#else
  struct timeval tval;
  uint64_t ret_tick;

  gettimeofday(&tval, NULL);

  ret_tick = tval.tv_sec * 1000L + tval.tv_usec / 1000L;
  return ret_tick;
#endif
}

void util_sleep(uint32_t millisecond) {
#ifdef _MSC_VER
  Sleep(millisecond);
#else
  usleep(millisecond * 1000);
#endif
}

size_t get_file_size(const char* path) {
  size_t filesize = -1;
  struct stat statbuff;
  if (stat(path, &statbuff) < 0) {
    return filesize;
  } else {
    filesize = statbuff.st_size;
  }
  return filesize;
}

char* long2ip(const unsigned int in) {
  unsigned short v1, v2, v3, v4;
  v4 = in % 256;
  v3 = (in >> 8) % 256;
  v2 = (in >> 16) % 256;
  v1 = (in >> 24) % 256;
  static char output[16];
  sprintf_s(output, sizeof(output), "%hd.%hd.%hd.%hd", v1, v2, v3, v4);
  return output;
}

unsigned int ip2long(const char* ip) {
  unsigned short v1, v2, v3, v4;
  sscanf_s(ip, "%hd.%hd.%hd.%hd", &v1, &v2, &v3, &v4);
  unsigned int vl = (v1 << 24) + (v2 << 16) + (v3 << 8) + v4;
  return vl;
}

void writePid() {
  uint32_t curPid;
#ifdef _MSC_VER
  curPid = (uint32_t)GetCurrentProcess();
#else
  curPid = (uint32_t)getpid();
#endif
  FILE* f = fopen("server.pid", "w");
  assert(f);
  char szPid[32];
  sprintf_s(szPid, sizeof(szPid), "%d", curPid);
  fwrite(szPid, strlen(szPid), 1, f);
  fclose(f);
}

NAMESPACE_END(util)
