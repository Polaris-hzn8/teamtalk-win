# 请求线程池实现http

---

windows版本的下载线程池http实现：

### TTThread

```cpp
class UTILITY_CLASS TTThread
{
public:
    TTThread();
    ~TTThread();

	BOOL create();
	void destory();
	BOOL wait(DWORD dwWaitTime);
	inline DWORD getThreadId() { return m_dwThreadID; }

protected:
	virtual UInt32 process();

private:
	static UInt32 __stdcall _threadProc(void *lpParam);

	HANDLE		m_hThread;
	DWORD		m_dwThreadID;
};
```

### TTHttpThread

```cpp
class TTHttpThread : public util::TTThread
{
	friend class HttpPoolModule_Impl;
public:
	TTHttpThread();
	void shutdown();
private:
	virtual UInt32 process();
	BOOL m_bContinue;
};
```

### HttpPoolModule_Impl

```cpp
class HttpPoolModule_Impl final : public module::IHttpPoolModule
{
	friend class TTHttpThread;
public:
	HttpPoolModule_Impl();
    virtual ~HttpPoolModule_Impl();

	virtual void    pushHttpOperation(module::IHttpOperation* pOperaion, BOOL bHighPriority = FALSE);
	virtual void    shutdown();
private:
	BOOL  _launchThread();			// 线程增加
	void  _cancelAllOperations();	// 取消所有任务

	std::list<module::IHttpOperation*>		m_lstHttpOpers;		// http操作队列
	std::vector<TTHttpThread*>				m_vecHttpThread;	// http线程池
	HANDLE									m_hSemaphore;
	CLock									m_mtxLock;

	int										m_maxThreadCount;	// 线程池最大线程数
	volatile BOOL							m_bShutdown;		// 是否关闭
};
```

### 通用代码抽象

![image-20251014100037486](C:\Users\vamtoo\AppData\Roaming\Typora\typora-user-images\image-20251014100037486.png)

```cpp

```





























