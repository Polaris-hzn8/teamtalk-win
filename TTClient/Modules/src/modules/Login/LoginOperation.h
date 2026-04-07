
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 执行登录操作
*/

#ifndef LOGINOPERATION_9610A313_DC31_429E_B9E9_09A34ABA8063_H__
#define LOGINOPERATION_9610A313_DC31_429E_B9E9_09A34ABA8063_H__

#include <modules/Base/ICallbackOpertaion.h>
#include <protocol/im.Login.pb.h>

enum
{
	LOGIN_FAIL = -1,            //登录失败
	LOGIN_OK = 0,               //登录成功
};

// 登录参数
struct LoginParam
{
	Int8            result;				// 登录结果
	UInt8			server_result;		// 服务器返回结果
	UInt8           mySelectedStatus;	// 用户选择状态
	UInt32          serverTime;			// 服务器时间戳
	CString			csUserName;			// 用户名
	CString			errInfo;			// 错误信息
	std::string		password;			// 密码

	LoginParam():
		result(LOGIN_FAIL),
		server_result(IM::BaseDefine::REFUSE_REASON_NONE),
		mySelectedStatus(IM::BaseDefine::USER_STATUS_ONLINE),
		serverTime(0)
	{
	}
};

// 登录操作
class LoginOperation : public module::ICallbackOpertaion
{
public:
	LoginOperation(module::IOperationDelegate callback, LoginParam& param);
    virtual ~LoginOperation();

public:
	virtual void processOpertion();
	virtual void release();

private:
	LoginParam			m_loginParam;
};

#endif// LOGINOPERATION_9610A313_DC31_429E_B9E9_09A34ABA8063_H__
