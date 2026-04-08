
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 一些比较杂的功能接口函数和全局变量定义
*/

#ifndef MISCMODULE_A3EEE277_68C9_4F13_96CD_1C0AB4033F12_H__
#define MISCMODULE_A3EEE277_68C9_4F13_96CD_1C0AB4033F12_H__

#include <modules/Base/ModuleBase.h>
#include <modules/IMiscModule.h>

class MiscModule_Impl : public module::IMiscModule {
 public:
  MiscModule_Impl();
  virtual ~MiscModule_Impl();
  virtual void release();

 public:
  virtual CString getUsersDir();
  virtual CString getTTCommonAppdata();
  virtual CString getCurAccountDir();
  virtual CString getDownloadDir();
  virtual CString getDownloadDirByToday();
  virtual CString getDataDir();
  virtual CString getDefaultAvatar();
  virtual CString getUserTempDir();
  virtual CString getDumpDir();
  virtual CString getFileRecvDir();             // 文件保存路径
  virtual CString getTTCommonAppdataUserDir();  // 获取系统数据目录
  virtual CString GetAudioFileSavedPath();      // 音频文件保存目录
  virtual CString getEmotionFilesDir();
  virtual CString makeShortTimeDescription(IN UInt32 Intime);

  virtual void playSysConfigSound();  // 根据设置的声音
  virtual void playSound(const CString& path);
  virtual void quitTheApplication();
  virtual CString getAppTitle();
  virtual void asynOpenWebBrowser(CString& url, Int32 nFlag = SW_SHOWMAXIMIZED);
  virtual void doProcess1(IN std::string& pData, OUT std::string& pOutData);
  virtual void doProcess2(IN std::string& pData, OUT std::string& pOutData);
};

#endif  // MISCMODULE_A3EEE277_68C9_4F13_96CD_1C0AB4033F12_H__
