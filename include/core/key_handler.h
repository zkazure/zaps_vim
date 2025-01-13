#pragma once

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <sdkddkver.h>
#include <windows.h>
#else
#include <windef.h>
#include <winuser.h>
#endif

#include "../mode/mode_manager.h"
#include "window_manager.h"

class KeyHandler {
public:
    explicit KeyHandler(ModeManager* modeManager);
    ~KeyHandler();

    bool registerGlobalHotkeys();
    void unregisterGlobalHotkeys();
    void handleKeyEvent(DWORD key);

private:
    ModeManager* modeManager;
    WindowManager windowManager;
    bool isAltPressed;
    bool isCtrlPressed;

    // 窗口切换相关方法
    void switchToPreviousWindow();
    void switchToNextWindow();
    void switchToNextTab();
    void switchToPreviousTab();
}; 