
/*
  Reviser: Polaris_hzn8
  Email: lch2022fox@163.com
  Github: https://github.com/Polaris-hzn8
  brief: 异步操作执行单位
*/

#ifndef IOPERATION123_D8CF1B19_B95A_4A75_82FB_7572A1BB9A30_H__
#define IOPERATION123_D8CF1B19_B95A_4A75_82FB_7572A1BB9A30_H__

#include <memory>
#include "GlobalDefine.h"
#include "network/networkdll.h"

NAMESPACE_BEGIN(imcore)

struct NETWORK_DLL IOperation
{
public:
	virtual void process() = 0;
	virtual void release() = 0;
};

NAMESPACE_END(imcore)

#endif// IOPERATION123_D8CF1B19_B95A_4A75_82FB_7572A1BB9A30_H__
