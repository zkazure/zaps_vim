#include "core/window_manager.h"
#include <algorithm>

WindowManager::WindowManager() : currentWindow(NULL) {
    updateWindowList();
}

WindowManager::~WindowManager() {
}

bool WindowManager::switchToWindow(HWND hwnd) {
    if (!isValidWindow(hwnd)) {
        return false;
    }

    // 激活窗口
    if (IsIconic(hwnd)) {
        ShowWindow(hwnd, SW_RESTORE);
    }
    SetForegroundWindow(hwnd);
    currentWindow = hwnd;
    return true;
}

bool WindowManager::switchToNextWindow() {
    updateWindowList();
    if (windowList.empty()) {
        return false;
    }

    auto it = std::find(windowList.begin(), windowList.end(), currentWindow);
    if (it == windowList.end() || ++it == windowList.end()) {
        it = windowList.begin();
    }

    return switchToWindow(*it);
}

bool WindowManager::switchToPreviousWindow() {
    updateWindowList();
    if (windowList.empty()) {
        return false;
    }

    auto it = std::find(windowList.begin(), windowList.end(), currentWindow);
    if (it == windowList.end() || it == windowList.begin()) {
        it = windowList.end() - 1;
    } else {
        --it;
    }

    return switchToWindow(*it);
}

bool WindowManager::closeCurrentWindow() {
    if (!currentWindow || !IsWindow(currentWindow)) {
        return false;
    }

    PostMessage(currentWindow, WM_CLOSE, 0, 0);
    return true;
}

HWND WindowManager::getCurrentWindow() const {
    return currentWindow;
}

std::vector<HWND> WindowManager::getWindowList() const {
    return windowList;
}

std::string WindowManager::getWindowTitle(HWND hwnd) const {
    if (!hwnd) {
        return "";
    }

    char title[256];
    GetWindowTextA(hwnd, title, sizeof(title));
    return std::string(title);
}

void WindowManager::maximizeWindow(HWND hwnd) {
    if (isValidWindow(hwnd)) {
        ShowWindow(hwnd, SW_MAXIMIZE);
    }
}

void WindowManager::minimizeWindow(HWND hwnd) {
    if (isValidWindow(hwnd)) {
        ShowWindow(hwnd, SW_MINIMIZE);
    }
}

void WindowManager::restoreWindow(HWND hwnd) {
    if (isValidWindow(hwnd)) {
        ShowWindow(hwnd, SW_RESTORE);
    }
}

void WindowManager::moveWindow(HWND hwnd, int x, int y, int width, int height) {
    if (isValidWindow(hwnd)) {
        SetWindowPos(hwnd, NULL, x, y, width, height, SWP_NOZORDER);
    }
}

void WindowManager::updateWindowList() {
    windowList.clear();
    EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM>(this));
    
    if (currentWindow == NULL && !windowList.empty()) {
        currentWindow = windowList[0];
    }
}

bool WindowManager::isValidWindow(HWND hwnd) const {
    return hwnd != NULL && IsWindow(hwnd) && IsWindowVisible(hwnd);
}

BOOL CALLBACK WindowManager::enumWindowsProc(HWND hwnd, LPARAM lParam) {
    WindowManager* manager = reinterpret_cast<WindowManager*>(lParam);
    
    // 检查窗口是否可见且有标题
    if (IsWindowVisible(hwnd)) {
        char title[256];
        if (GetWindowTextA(hwnd, title, sizeof(title)) > 0) {
            manager->windowList.push_back(hwnd);
        }
    }
    
    return TRUE;
} 