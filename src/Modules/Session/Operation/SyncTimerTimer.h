
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: ͬ��������ʱ��timer
*/

#ifndef SYNCTIMERTIMER_33883969_3CB9_47FD_BC38_4E860C0731F8_H__
#define SYNCTIMERTIMER_33883969_3CB9_47FD_BC38_4E860C0731F8_H__

#include "Modules/IEvent.h"
#include "Modules/ITimerEvent.h"

class SyncTimeTimer : public module::ITimerEvent
{
public:
    SyncTimeTimer();
    virtual ~SyncTimeTimer() = default;
	virtual void process();
    virtual void release();
public:
    inline Int32 getTime()const { return m_serverTime;}
    inline void setTime(UInt32 time) { m_serverTime = time;}

private:
    UInt32                  m_serverTime;           //������ʱ��
    UInt32                  m_timeCount;            //ʱ�������
};

#endif// SYNCTIMERTIMER_33883969_3CB9_47FD_BC38_4E860C0731F8_H__
