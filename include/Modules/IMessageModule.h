
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 历史消息DB相关接口
*/

#ifndef IHITORYMSGMODULE_D042F2F2_05B0_45E6_9746_344A76279AE8_H__
#define IHITORYMSGMODULE_D042F2F2_05B0_45E6_9746_344A76279AE8_H__

#include <list>
#include "GlobalDefine.h"
#include "MessageEntity.h"
#include "Modules/ModuleDll.h"

class MessageEntity;
class TransferFileEntity;

NAMESPACE_BEGIN(module)

class MODULE_API IMessageModule
{
public:
	virtual BOOL getHistoryMessage(IN const std::string& sId, IN UInt32 nMsgCount
								  ,IN BOOL scrollBottom, OUT std::vector<MessageEntity>& msgList) = 0;
	virtual void setSessionTopMsgId(IN const std::string& sId,IN UInt32 msgId) = 0;

	// 运行时消息相关
	// 断线重连的情况下要清理消息
	virtual void removeMessageBySId(IN const std::string& sId) = 0;
	virtual void removeAllMessage() = 0;
	virtual BOOL pushMessageBySId(IN const std::string& sId,IN MessageEntity& msg) = 0;
	virtual UInt32 getTotalUnReadMsgCount(void) = 0;
};

MODULE_API IMessageModule* getMessageModule();

NAMESPACE_END(module)

#endif// IHITORYMSGMODULE_D042F2F2_05B0_45E6_9746_344A76279AE8_H__
