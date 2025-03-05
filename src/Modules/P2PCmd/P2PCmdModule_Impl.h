
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 客户端与客户端之间数据传输 如:正在输入、窗口抖动等
*/

#ifndef P2PCMDMODULE_IMPL_A50A4241_F1E2_4E7D_A738_70C2E5EE82BE_H__
#define P2PCMDMODULE_IMPL_A50A4241_F1E2_4E7D_A738_70C2E5EE82BE_H__

#include "Modules/IP2PCmdModule.h"

class P2PCmdModule_Impl : public module::IP2PCmdModule
{
public:
    P2PCmdModule_Impl() = default;
    virtual ~P2PCmdModule_Impl() = default;
	virtual void onPacket(imcore::TTPBHeader& header, std::string& pbBody);
public:
	virtual BOOL tcpSendShakeWindowCMD(IN std::string sToID);
	virtual void tcpSendWritingCMD(IN std::string sToID, IN const BOOL bWriting);
private:
	void _parseMsgJsonData(IN std::string sJsonData, OUT UInt32& nServiceID, OUT UInt32& nCmdID);
	void _makeJsonData(IN UINT32 nServiceID, IN UINT32 nCmdID, IN std::string sContent, OUT std::string& sJsonData);
private:
	/* 服务器端拆包 */
	void _p2pCmdNotifyResponse(std::string& pbBody);
};

#endif// P2PCMDMODULE_IMPL_A50A4241_F1E2_4E7D_A738_70C2E5EE82BE_H__
