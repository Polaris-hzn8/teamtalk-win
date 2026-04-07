
#ifndef FILETRANSFERUITHREAD_16C2B941_3E94_4B6F_B488_0B82EC2B3F26_H__
#define FILETRANSFERUITHREAD_16C2B941_3E94_4B6F_B488_0B82EC2B3F26_H__

#include <list>
#include <Utility/Lock.h>
#include <utility/TTThread.h>

using namespace util;
class FileTransferSocket;

#define WM_FILE_TRANSFER		WM_USER + 888

class FileTransferUIThread : public TTThread
{
public:
    FileTransferUIThread();
    virtual ~FileTransferUIThread();
public:
	void Shutdown();
	virtual UInt32 process();

public:
	/**
	 * 在UI thread中异步创建文件传输socket
	 *
	 * @param   std::string & taskId 文件任务中心的id
	 * @return  void
	 * @exception there is no any exception to throw.
	 */	
	void openFileSocketByTaskId(std::string& taskId);
	/**
	* 在UI thread中关闭文件传输socket
	*
	* @param   std::string & taskId 文件任务中心的id
	* @return  void
	* @exception there is no any exception to throw.
	*/
	void closeFileSocketByTaskId(std::string& taskId);
	/**
	 * 从文件传输中心获取和接受的文件传输
	 *
	 * @param   std::string & taskId
	 * @return  BOOL
	 * @exception there is no any exception to throw.
	 */	
	BOOL acceptFileTransfer(const std::string& taskId);
	BOOL rejectFileTransfer(const std::string& taskId);
	BOOL cancelFileTransfer(const std::string& taskId);

private:
	HWND _createWnd();
	void _releaseWnd();
	void _closeAllFileSockets();
	static LRESULT _stdcall _WndProc(HWND hWnd
		, UINT message
		, WPARAM wparam
		, LPARAM lparam);
	FileTransferSocket* _findFileSocketByTaskId(const std::string& taskId);

public:
	HWND							m_hWnd;
	std::list<FileTransferSocket*>	m_lstFileTransSockets;
	CLock				m_lock;
};

#endif// FILETRANSFERUITHREAD_16C2B941_3E94_4B6F_B488_0B82EC2B3F26_H__
