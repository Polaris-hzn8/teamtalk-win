# HTTP请求线程池实现

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

