
#ifndef _UTILITY_DLL_H_
#define _UTILITY_DLL_H_

#ifndef UTILITY_DLL
#define UTILITY_API __declspec(dllimport)
#define UTILITY_CLASS __declspec(dllimport)
#else
#define UTILITY_API __declspec(dllexport)
#define UTILITY_CLASS __declspec(dllexport)
#endif

#endif  // _UTILITY_DLL_H_
