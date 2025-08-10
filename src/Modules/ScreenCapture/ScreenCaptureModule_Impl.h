
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef SCREENCAPTUREMODULE_IMPL_1403B705_6422_4459_829B_20F1F6DB205C_H__
#define SCREENCAPTUREMODULE_IMPL_1403B705_6422_4459_829B_20F1F6DB205C_H__

#include "Modules/IScreenCaptureModule.h"

class ScreenCaptureModule_Impl final :public module::IScreenCaptureModule
{
public:
    BOOL initCapture(__in HWND hWnd);
    BOOL startCapture(__in std::wstring strSavePath, __in BOOL bMinimizeWindow /* = FALSE */);
    void cancelCapture();

    module::ScreenCaptureHotkeyId shouldHandle(__in LPARAM lParam);

    void onScreenCaptureFinish(__in std::wstring resultPicPath);
};

#endif// SCREENCAPTUREMODULE_IMPL_1403B705-6422-4459-829B-20F1F6DB205C_H__

