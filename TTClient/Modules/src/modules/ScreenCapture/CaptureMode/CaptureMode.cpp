
#include "stdafx.h"
#include <modules/ScreenCapture/CaptureMode/AutoSelectMode.h>
#include <modules/ScreenCapture/CaptureMode/CaptureMode.h>
#include <modules/ScreenCapture/CaptureMode/ManalEditMode.h>
#include <modules/ScreenCapture/CaptureMode/ManalSelectMode.h>

CaptureModeMgr::CaptureModeMgr() : m_emCurrentMode(CM_MIN) {}

CaptureMode CaptureModeMgr::changeMode(__in CaptureMode emMode) {
  CaptureMode emCurrentMode = m_emCurrentMode;
  m_emCurrentMode = emMode;

  return emCurrentMode;
}

void CaptureModeMgr::handleMouseMsg(__in UINT uMsg, __in int xPos, __in int yPos) {
  IModeMsgHandler* msgHandler = getModeHandler();
  if (!msgHandler)
    return;

  if (WM_MOUSEMOVE == uMsg) {
    msgHandler->onMouseMove(xPos, yPos);
  } else if (WM_LBUTTONDOWN == uMsg) {
    msgHandler->onLButtonDown(xPos, yPos);
  } else if (WM_LBUTTONUP == uMsg) {
    msgHandler->onLButtonUp(xPos, yPos);
  } else if (WM_LBUTTONDBLCLK == uMsg) {
    msgHandler->onLButtonDBClick(xPos, yPos);
  }
}

IModeMsgHandler* CaptureModeMgr::getModeHandler() {
  if (CM_AUTO_SELECT == m_emCurrentMode) {
    return AutoSelectMode::Instance();
  } else if (CM_MANAL_SELECT == m_emCurrentMode) {
    return ManalSelectMode::Instance();
  } else if (CM_MANAL_EDIT == m_emCurrentMode) {
    return ManalEditMode::Instance();
  }

  return NULL;
}

BOOL CaptureModeMgr::snapshotWindows() {
  return AutoSelectMode::Instance()->snapshotWindows();
}

void CaptureModeMgr::clear() {
  m_emCurrentMode = CM_MIN;
  AutoSelectMode::Instance()->clear();
  ManalSelectMode::Instance()->clear();
  ManalEditMode::Instance()->clear();
}
