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

#include <vector>
#include <string>

class WindowManager {
public:
    WindowManager();
    ~WindowManager();

    // 窗口操作
    bool switchToWindow(HWND hwnd);
    bool switchToNextWindow();
    bool switchToPreviousWindow();
    bool closeCurrentWindow();
    
    // 窗口信息获取
    HWND getCurrentWindow() const;
    std::vector<HWND> getWindowList() const;
    std::string getWindowTitle(HWND hwnd) const;
    
    // 窗口布局
    void maximizeWindow(HWND hwnd);
    void minimizeWindow(HWND hwnd);
    void restoreWindow(HWND hwnd);
    void moveWindow(HWND hwnd, int x, int y, int width, int height);

private:
    HWND currentWindow;
    std::vector<HWND> windowList;

    // 辅助方法
    void updateWindowList();
    bool isValidWindow(HWND hwnd) const;
    static BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam);
}; 