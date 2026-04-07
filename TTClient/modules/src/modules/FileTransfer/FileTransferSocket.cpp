
#include "stdafx.h"
#include <protocol/IM.File.pb.h>
#include <protocol/IM.Other.pb.h>

#include <utility/utilCommonAPI.h>

#include <modules/IMiscModule.h>
#include <modules/ISysConfigModule.h>
#include <modules/IFileTransferModule.h>
#include <modules/FileTransfer/TransferFile.h>
#include <modules/FileTransfer/TransferManager.h>
#include <modules/FileTransfer/FileTransferSocket.h>

#include <network/ImCore.h>
#include <network/core/im_conn.h>
#include <network/core/ImPduBase.h>

FileTransferSocket::FileTransferSocket(std::string& taskId)
	:m_pPingTimer(nullptr),
	m_sTaskId(taskId)
{

}

FileTransferSocket::~FileTransferSocket(void)
{

}

BOOL FileTransferSocket::connect(const CString &linkaddr, UInt16 port)
{
    m_socketHandle = imcore::IMLibCoreConnect(util::cStringToString(linkaddr), port);
    imcore::IMLibCoreRegisterCallback(m_socketHandle, this);

	return TRUE;
}

BOOL FileTransferSocket::shutdown()
{
    stopHeartbeat();
    //_stopServerPingTimer();
    imcore::IMLibCoreShutdown(m_socketHandle);
	return TRUE;
}

void FileTransferSocket::sendPacket(IN UInt16 moduleId, IN UInt16 cmdId, IN google::protobuf::MessageLite* pbBody)
{
    m_TTPBHeader.clear();
    m_TTPBHeader.setModuleId(moduleId);
    m_TTPBHeader.setCommandId(cmdId);

    UInt32 length = imcore::HEADER_LENGTH + pbBody->ByteSize();//计算总长度
    m_TTPBHeader.setLength(length);

    std::unique_ptr<byte> data(new byte[length]);
    ZeroMemory(data.get(), length);
    memcpy(data.get(), m_TTPBHeader.getSerializeBuffer(), imcore::HEADER_LENGTH);//复制头
    if (!pbBody->SerializeToArray(data.get() + imcore::HEADER_LENGTH, pbBody->ByteSize()))
    {
        LOG__(ERR, _T("pbBody SerializeToArray failed"));
        return;
    }
    imcore::IMLibCoreWrite(m_socketHandle, data.get(), length);
}

void FileTransferSocket::startHeartbeat() 
{
	if (!m_pPingTimer)
		m_pPingTimer = new PingFileSevTimer(this);
	module::getEventManager()->scheduleTimer(m_pPingTimer, 5, TRUE);
}

void FileTransferSocket::stopHeartbeat()
{
	if (m_pPingTimer)
		module::getEventManager()->killTimer(m_pPingTimer);
	m_pPingTimer = 0;
}

void FileTransferSocket::onReceiveData(const char* data, int32_t size)
{
    std::string pbBody;
    imcore::TTPBHeader pbHeader; 
	try
	{
        pbHeader.unSerialize((byte*)data, imcore::HEADER_LENGTH);
        pbBody.assign(data + imcore::HEADER_LENGTH, size - imcore::HEADER_LENGTH);

        if (IM::BaseDefine::OtherCmdID::CID_OTHER_HEARTBEAT == pbHeader.getCommandId()
            && IM::BaseDefine::ServiceID::SID_OTHER == pbHeader.getModuleId())
            return;
	}
	catch (CPduException e)
	{
		LOG__(ERR, _T("onPacket CPduException serviceId:%d,commandId:%d,errCode:%d")
			, e.GetModuleId(), e.GetCommandId(), e.GetErrorCode());
		return;
	}
	catch (...)
	{
		LOG__(ERR, _T("FileTransferSocket onPacket unknown exception"));
		return;
	}
    UInt16 ncmdid = pbHeader.getCommandId();
    switch (ncmdid)
	{	 
    case IM::BaseDefine::FileCmdID::CID_FILE_LOGIN_RES:
        _fileLoginResponse(pbBody);
		break;
    case IM::BaseDefine::FileCmdID::CID_FILE_PULL_DATA_REQ://拉取文件数据请求
        _filePullDataReqResponse(pbBody);
		break;
    case IM::BaseDefine::FileCmdID::CID_FILE_PULL_DATA_RSP://拉取文件数据响应
        _filePullDataRspResponse(pbBody);
		break;
    case IM::BaseDefine::FileCmdID::CID_FILE_STATE://
        _fileState(pbBody);
	default:
		break;
	}
}


void FileTransferSocket::onConnectDone()
{
	LOG__(APP, _T("FileTransferSocket::onConnected()"));
	startHeartbeat();

	TransferFileEntity info;
    if (!TransferFileEntityManager::getInstance()->getFileInfoByTaskId(m_sTaskId, info))
    {
        LOG__(APP, _T("Can't get the file info,task id:%s"),util::stringToCString(m_sTaskId));
        return;
    }
		
	//根据taskid获取token和client_mode
	IM::File::IMFileLoginReq imFileLoginReq;
	imFileLoginReq.set_user_id(module::getSysConfigModule()->userId());
	imFileLoginReq.set_task_id(info.sTaskID);
	imFileLoginReq.set_file_role(static_cast<IM::BaseDefine::ClientFileRole>(info.nClientMode));

    LOG__(APP, _T("IMFileLoginReq,sTaskID:%s,nClientMode:%d"), util::stringToCString(info.sTaskID), info.nClientMode);
	//send packet
    LOG__(APP, _T("IMFileLoginReq,taskId:%s"), util::stringToCString(info.sTaskID));
    sendPacket(IM::BaseDefine::ServiceID::SID_FILE, IM::BaseDefine::FileCmdID::CID_FILE_LOGIN_REQ, &imFileLoginReq);

	//CImPduClientFileLoginReq pduFileLoginReq(module::getSysConfigModule()->userID().c_str()
	//	, "", info.sTaskID.c_str(), );
	//sendPacket(&pduFileLoginReq);
}
void FileTransferSocket::onClose()
{
	stopHeartbeat();
}


BOOL FileTransferSocket::startFileTransLink()
{
	TransferFileEntity FileInfo;
	if (TransferFileEntityManager::getInstance()->getFileInfoByTaskId(m_sTaskId, FileInfo))
	{
		//连接文件服务器
		LOG__(APP, _T("connect IP=%s,Port=%d"), util::stringToCString(FileInfo.sIP), FileInfo.nPort);
		connect(util::stringToCString(FileInfo.sIP), FileInfo.nPort);
		//connect(util::stringToCString(module::FILETRANSFER_IP), module::FILETRANSFER_PORT);
		return TRUE;
	}
	LOG__(ERR, _T("can't find the TaskId"));
	return FALSE;
}

void FileTransferSocket::stopfileTransLink()
{
	shutdown();
	stopHeartbeat();
}

void FileTransferSocket::_fileLoginResponse(IN std::string& body)
{
	IM::File::IMFileLoginRsp imFileLoginRsp;
    if (!imFileLoginRsp.ParseFromString(body))
    {
        LOG__(ERR, _T("parse failed,body:%s"), util::stringToCString(body));
        return;
    }
	if (imFileLoginRsp.result_code() != 0)
	{
		LOG__(ERR, _T("file server login failed! "));
		return;
	}
	//登录
	std::string taskId = imFileLoginRsp.task_id();
	TransferFileEntity fileEntity;
	if (!TransferFileEntityManager::getInstance()->getFileInfoByTaskId(taskId, fileEntity))
	{
		LOG__(ERR, _T("file server login:can't find the fileInfo "));
		return;
	}

	LOG__(APP, _T("IMFileLoginRsp, file server login succeed"));
	//根据文件角色通知对应的模块
	if (IM::BaseDefine::ClientFileRole::CLIENT_REALTIME_SENDER == fileEntity.nClientMode
		|| IM::BaseDefine::ClientFileRole::CLIENT_OFFLINE_UPLOAD == fileEntity.nClientMode)
	{
		module::getFileTransferModule()->asynNotifyObserver(module::KEY_FILETRANSFER_SENDFILE, fileEntity.sTaskID);
	}
	else if (IM::BaseDefine::ClientFileRole::CLIENT_REALTIME_RECVER == fileEntity.nClientMode
		|| IM::BaseDefine::ClientFileRole::CLIENT_OFFLINE_DOWNLOAD == fileEntity.nClientMode)
	{
		module::getFileTransferModule()->asynNotifyObserver(module::KEY_FILETRANSFER_REQUEST, fileEntity.sTaskID);
	}
}

void FileTransferSocket::_filePullDataReqResponse(IN std::string& body)//回复拉取数据请求
{
	IM::File::IMFilePullDataReq imFilePullDataReq;
    if (!imFilePullDataReq.ParseFromString(body))
    {
        LOG__(ERR, _T("parse failed,body:%s"), util::stringToCString(body));
        return;
    }
	UInt32 fileSize = imFilePullDataReq.data_size();
	UInt32 fileOffset = imFilePullDataReq.offset();
	std::string taskId = imFilePullDataReq.task_id();
	
	TransferFileEntity fileEntity;
	if (!TransferFileEntityManager::getInstance()->getFileInfoByTaskId(taskId, fileEntity))
	{
		LOG__(ERR, _T("PullDataReqResponse: can't find the fileInfo"));
		return;
	}
	LOG__(DEBG, _T("send:taskId=%s,filesize=%d,name=%s,BolckSize=%d")
		,util::stringToCString(fileEntity.sTaskID)
		,fileEntity.nFileSize
		,fileEntity.getRealFileName()
        ,fileSize);
	std::string buff;
	if (nullptr == fileEntity.pFileObject)
	{
		LOG__(ERR, _T("PullDataReqResponse: file boject Destoryed!"));
		return;
	}
	fileEntity.pFileObject->readBlock(fileOffset, fileSize, buff);//读取文件数据块
	IM::File::IMFilePullDataRsp imFilePullDataRsp;//todo check
    imFilePullDataRsp.set_result_code(0);
	imFilePullDataRsp.set_task_id(taskId);
	imFilePullDataRsp.set_user_id(util::stringToInt32(fileEntity.sFromID));
	imFilePullDataRsp.set_offset(fileOffset);
    imFilePullDataRsp.set_file_data((void*)buff.data(), fileSize);

    //send packet
    sendPacket(IM::BaseDefine::ServiceID::SID_FILE, IM::BaseDefine::FileCmdID::CID_FILE_PULL_DATA_RSP
        , &imFilePullDataRsp);

	fileEntity.nProgress = fileOffset + fileSize;
	if (fileEntity.nProgress < fileEntity.nFileSize)
	{
		//继续发送
		TransferFileEntityManager::getInstance()->updateFileInfoBysTaskID(fileEntity);//更新文件信息
		module::getFileTransferModule()->asynNotifyObserver(module::KEY_FILESEVER_UPDATA_PROGRESSBAR
            , fileEntity.sTaskID);
	}
	else//传输完成
	{
		if (fileEntity.pFileObject)
		{
			delete fileEntity.pFileObject;
			fileEntity.pFileObject = nullptr;
		}
		module::getFileTransferModule()->asynNotifyObserver(module::KEY_FILESEVER_PROGRESSBAR_FINISHED
            , fileEntity.sTaskID);
	}
	TransferFileEntityManager::getInstance()->updateFileInfoBysTaskID(fileEntity);
}

void FileTransferSocket::_filePullDataRspResponse(IN std::string& body)//处理拉取数据响应
{
	IM::File::IMFilePullDataRsp imFilePullDataRsp;
    if (!imFilePullDataRsp.ParseFromString(body))
    {
        LOG__(ERR, _T("parse failed,body:%s"), util::stringToCString(body));
        return;
    }
	UInt32 nRes = imFilePullDataRsp.result_code();
	if (0 != nRes)
	{
		LOG__(ERR, _T("PullDataRspResponse: error result:%d"),nRes);
		return;
	}
	std::string taskId = imFilePullDataRsp.task_id();
	const std::string& strData = imFilePullDataRsp.file_data();//todo 这里需要检查是否完整
	void* pData = (void*)(strData.data());
	UInt32 nBlockSize = strData.size();
	UInt32 fileOffset = imFilePullDataRsp.offset();
	TransferFileEntity fileEntity;
	if (!TransferFileEntityManager::getInstance()->getFileInfoByTaskId(taskId, fileEntity))
	{
		LOG__(ERR, _T("can't find the fileInfo"));
		return;
	}
	LOG__(DEBG, _T("receive:taskId=%s,filesize=%d,name=%s,BolckSize=%d")
		, util::stringToCString(fileEntity.sTaskID)
		, fileEntity.nFileSize
		, fileEntity.getRealFileName()
        , nBlockSize);

	//写入文件...
	if (!fileEntity.pFileObject->writeBlock(fileOffset, nBlockSize, pData))
	{
		LOG__(DEBG, _T("writeBlock failed "));
		return;
	}

	fileEntity.nProgress = fileOffset + nBlockSize;
	if (fileEntity.nProgress < fileEntity.nFileSize)
	{
		//继续请求
		TransferFileEntityManager::getInstance()->updateFileInfoBysTaskID(fileEntity);//更新文件信息
		module::getFileTransferModule()->asynNotifyObserver(module::KEY_FILESEVER_UPDATA_PROGRESSBAR
            , fileEntity.sTaskID);

		//继续请求file block req...
		int mode = fileEntity.nClientMode == IM::BaseDefine::ClientFileRole::CLIENT_OFFLINE_DOWNLOAD ? IM::BaseDefine::TransferFileType::FILE_TYPE_OFFLINE : IM::BaseDefine::TransferFileType::FILE_TYPE_ONLINE;
		IM::File::IMFilePullDataReq imFilePullDataReq;
		imFilePullDataReq.set_task_id(taskId);
		imFilePullDataReq.set_user_id(util::stringToInt32(fileEntity.sToID));
		imFilePullDataReq.set_trans_mode(static_cast<IM::BaseDefine::TransferFileType>(mode));
		imFilePullDataReq.set_offset(fileEntity.nProgress);

        UInt32 pullSize = fileEntity.nFileSize - fileEntity.nProgress;
        pullSize > nBlockSize ? imFilePullDataReq.set_data_size(nBlockSize) : imFilePullDataReq.set_data_size(pullSize);
		
		// 发送请求
        sendPacket(IM::BaseDefine::ServiceID::SID_FILE, IM::BaseDefine::FileCmdID::CID_FILE_PULL_DATA_REQ, &imFilePullDataReq);
	}
	else//传输完成
	{
		if (fileEntity.pFileObject)
		{
			delete fileEntity.pFileObject;
			fileEntity.pFileObject = nullptr;
		}

        //发送文件传输完成状态
        IM::File::IMFileState imFileState;
        imFileState.set_state(IM::BaseDefine::ClientFileState::CLIENT_FILE_DONE);
        imFileState.set_task_id(taskId);
        imFileState.set_user_id(util::stringToInt32(fileEntity.sToID));
        sendPacket(IM::BaseDefine::ServiceID::SID_FILE, IM::BaseDefine::FileCmdID::CID_FILE_STATE, &imFileState);

		TransferFileEntityManager::getInstance()->updateFileInfoBysTaskID(fileEntity);
		module::getFileTransferModule()->asynNotifyObserver(module::KEY_FILESEVER_PROGRESSBAR_FINISHED, fileEntity.sTaskID);
	}
}

void FileTransferSocket::_fileState(IN std::string& body)
{
	IM::File::IMFileState imFileState;
    if (!imFileState.ParseFromString(body))
    {
        LOG__(ERR, _T("parse failed,body:%s"), util::stringToCString(body));
        return;
    }
	UINT32 nfileState = imFileState.state();

	std::string taskId = imFileState.task_id();
	TransferFileEntity fileEntity;
	if (!TransferFileEntityManager::getInstance()->getFileInfoByTaskId(taskId, fileEntity))
	{
		LOG__(ERR, _T("fileState:can't find the fileInfo "));
		return;
	}

	switch (nfileState)
	{
	case IM::BaseDefine::ClientFileState::CLIENT_FILE_PEER_READY:
		LOG__(APP, _T("fileState--CLIENT_FILE_PEER_READY "));
		break;
	case IM::BaseDefine::ClientFileState::CLIENT_FILE_CANCEL ://对方取消了传输
		LOG__(APP, _T("fileState--CLIENT_FILE_CANCEL "));
		{
            if (fileEntity.pFileObject)
            {
                delete fileEntity.pFileObject;
                fileEntity.pFileObject = nullptr;
            }
			TransferFileEntityManager::getInstance()->updateFileInfoBysTaskID(fileEntity);
			module::getFileTransferModule()->asynNotifyObserver(module::KEY_FILESEVER_UPLOAD_CANCEL, fileEntity.sTaskID);
		}
		break;
	case IM::BaseDefine::ClientFileState::CLIENT_FILE_REFUSE://对方拒绝了传输
		LOG__(APP, _T("fileState--CLIENT_FILE_REFUSE "));
		{
            if (fileEntity.pFileObject)
            {
                delete fileEntity.pFileObject;
                fileEntity.pFileObject = nullptr;
            }
			TransferFileEntityManager::getInstance()->updateFileInfoBysTaskID(fileEntity);
			module::getFileTransferModule()->asynNotifyObserver(module::KEY_FILESEVER_UPLOAD_REJECT, fileEntity.sTaskID);
		}
		break;
	case IM::BaseDefine::ClientFileState::CLIENT_FILE_DONE:
		LOG__(APP, _T("fileState--CLIENT_FILE_DONE "));
		if (fileEntity.pFileObject)
		{
			delete fileEntity.pFileObject;
			fileEntity.pFileObject = nullptr;
		}
		TransferFileEntityManager::getInstance()->updateFileInfoBysTaskID(fileEntity);
		module::getFileTransferModule()->asynNotifyObserver(module::KEY_FILESEVER_PROGRESSBAR_FINISHED, fileEntity.sTaskID);
		break;
	default:
		break;
	}
}

void FileTransferSocket::onReceiveError()
{

}

//////////////////////////////////////////////////////////////////////////
void PingFileSevTimer::release()
{
	delete this;
}

void PingFileSevTimer::process()
{
	imcore::IMLibCoreStartOperationWithLambda(
		[=]()
	{
        IM::Other::IMHeartBeat imHearBeat;
        m_pFileTransSocket->sendPacket(IM::BaseDefine::ServiceID::SID_OTHER
            , IM::BaseDefine::OtherCmdID::CID_OTHER_HEARTBEAT, &imHearBeat);
	}
		);
}

PingFileSevTimer::PingFileSevTimer(FileTransferSocket* pTransSocket)
:m_pFileTransSocket(pTransSocket)
{

}
