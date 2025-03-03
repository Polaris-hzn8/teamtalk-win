
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef DOLOGINSERVERHTTPOPERATION_D4296DCE_0662_447D_9F79_B058C0B9FC6D_H__
#define DOLOGINSERVERHTTPOPERATION_D4296DCE_0662_447D_9F79_B058C0B9FC6D_H__

#include "Modules/IHttpPoolModule.h"
#include <string>

enum
{
	DOLOGIN_SUCC = 0,
	DOLOGIN_FAIL = 1,
};

class DoLoginServerParam
{
public:
	UInt8		result = DOLOGIN_FAIL;
	CString		resMsg;
};

class DoLoginServerHttpOperation : public module::IHttpOperation
{
public:
	DoLoginServerHttpOperation(IN module::IOperationDelegate callback,IN DoLoginServerParam& param);
	virtual  ~DoLoginServerHttpOperation() = default;
public:
	virtual void processOpertion();
	virtual void release();
private:
	DoLoginServerParam			m_param;
};

#endif// DOLOGINSERVERHTTPOPERATION_D4296DCE_0662_447D_9F79_B058C0B9FC6D_H__
