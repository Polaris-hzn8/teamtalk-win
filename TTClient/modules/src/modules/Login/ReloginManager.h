
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 断线重连
*/

#ifndef RELOGINMANAGER_95607570_AE99_4D6C_B2F6_25CD0FD8A0FA_H__
#define RELOGINMANAGER_95607570_AE99_4D6C_B2F6_25CD0FD8A0FA_H__

#include <modules/Base/IEvent.h>
#include <memory>

class ReloginManager;
class ReloginManager
{
    friend class ReloginTimer;
public:
    ReloginManager();
    ~ReloginManager();
	void OnOperationCallback(std::shared_ptr<void> param);

public:
    void startReloginTimer(UInt32 second);
    void forceRelogin();
    
private:
    void doRelogin();

private:
    UInt32                      m_secondCount;//重连计时：3秒后重连，15秒
    BOOL                        m_bDoReloginNow;
};

#endif// RELOGINMANAGER_95607570_AE99_4D6C_B2F6_25CD0FD8A0FA_H__
