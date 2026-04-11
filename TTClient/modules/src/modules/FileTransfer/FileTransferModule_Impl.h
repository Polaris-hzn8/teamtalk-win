
#ifndef FILETRANSFER_IMPL_AB8D6DD0_25EF_4809_A857_9450EEA7CBFE_H__
#define FILETRANSFER_IMPL_AB8D6DD0_25EF_4809_A857_9450EEA7CBFE_H__

#include <modules/FileTransfer/TransferManager.h>
#include <modules/IFileTransferModule.h>

class FileTransferDialog;
class FileTransferModule_Impl : public module::IFileTransferModule {
 public:
  FileTransferModule_Impl();
  virtual ~FileTransferModule_Impl();
  virtual void onPacket(network::TTPBHeader& header, std::string& pbBody);

 public:
  // 发送文件
  virtual BOOL sendFile(IN const CString& sFilePath, IN const std::string& sSendToSID, IN BOOL bOnlineMode);
  virtual BOOL acceptFileTransfer(IN const std::string& sTaskId, IN const BOOL bAccept = TRUE);
  virtual BOOL doCancel(IN const std::string& sFileID);

  virtual void showFileTransferDialog();

  void MKOForFileTransferModuleCallback(const std::string& keyId, MKO_TUPLE_PARAM mkoParam);

 private:
  // 消息过滤器
  void _sendfileResponse(IN std::string& body);
  void _hasOfflineRes(IN std::string& body);
  void _fileNotify(IN std::string& body);

  BOOL _checkIfIsSending(IN CString sFilePath);  // 检查重复的文件名，防止重复发送
 private:
  FileTransferDialog* m_pFileTransferDialog;
};

#endif  // FILETRANSFER_IMPL_AB8D6DD0_25EF_4809_A857_9450EEA7CBFE_H__
