
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef SCREENSNAPSHOT_BC2EEFE8_E0DC_4340_A330_ADEA1587ABD1_H__
#define SCREENSNAPSHOT_BC2EEFE8_E0DC_4340_A330_ADEA1587ABD1_H__

#include "Common.h"
#include <vector>

class ScreenSnapshot :public Singleton<ScreenSnapshot>
{

public:
	ScreenSnapshot();
	BOOL snapshotScreen();
    BOOL updateRect(__in LPRECT lpRect);
	BOOL paintWndRect(__in HWND hWnd, __in LPRECT lpRect);
	BOOL saveRect(__in RECT &rc, __in std::wstring &savePath);

private:
    const int m_iDrawPenWidth = 3;

private:
    HBITMAP m_hDrawBitmap;
    HDC m_hDrawMemDC;

    HBITMAP m_hMemBitmap;
	HDC m_hMemDC;

    HBITMAP m_hBkBitmap;
    HDC m_hBkgMemDC;
};

#endif// SCREENSNAPSHOT_BC2EEFE8-E0DC-4340-A330-ADEA1587ABD1_H__
