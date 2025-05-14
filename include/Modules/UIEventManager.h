
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: UI事件代理窗口
*/

#ifndef UIEVENTMANAGER_7F7C0283_2B1D_4BB8_8052_ADBB35F055F3_H__
#define UIEVENTMANAGER_7F7C0283_2B1D_4BB8_8052_ADBB35F055F3_H__

#include <list>
#include <functional>
#include "ModuleDll.h"
#include "GlobalDefine.h"
#include "network/Lock.h"
#include "network/ErrorCode.h"

NAMESPACE_BEGIN(module)

using namespace imcore;

struct IEvent;
struct ITimerEvent;
struct TTTimer
{
	UInt64 nElapse;
	UInt32 nDelay;
	BOOL   bRepeat;
	ITimerEvent* pTimerEvent;

	TTTimer();
};

class MODULE_CLASS UIEventManager final
{
public:
	UIEventManager();
    ~UIEventManager();
public:
	IMCoreErrorCode startup();
	void            shutdown();
	IMCoreErrorCode asynFireUIEvent(IN const IEvent* const pEvent);
	IMCoreErrorCode	asynFireUIEventWithLambda(std::function<void()> eventRun);
	IMCoreErrorCode scheduleTimer(IN ITimerEvent* pTimerEvent, IN UInt32 delay, IN BOOL bRepeat);
	IMCoreErrorCode scheduleTimerWithLambda(IN UInt32 delay, IN BOOL bRepeat
										  , IN std::function<void()> timerRun
										  , OUT ITimerEvent** ppTimer);
	IMCoreErrorCode killTimer(IN ITimerEvent* pTimerEvent);

private:
	BOOL _registerClass();
	void _removeEvents();
	void _processTimer();
	void _processEvent(IEvent* pEvent, BOOL bRelease);

	static LRESULT _stdcall _WindowProc(HWND hWnd
		, UINT message
		, WPARAM wparam
		, LPARAM lparam);
private:
	UIEventManager& operator=(UIEventManager&);
	UIEventManager(const UIEventManager&);

private:
	HWND                    m_hWnd;
	CLock					m_lock;
	std::list<TTTimer>		m_lstTimers;
};

MODULE_API UIEventManager* getEventManager();

NAMESPACE_END(module)

#endif// UIEVENTMANAGER_7F7C0283_2B1D_4BB8_8052_ADBB35F055F3_H__
