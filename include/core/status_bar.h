#pragma once

#include <windows.h>
#include <string>
#include "core/mode_manager.h"

class StatusBar {
public:
    StatusBar();
    ~StatusBar();

    // 初始化状态栏
    bool initialize();

    // 更新状态栏内容
    void updateMode(Mode mode);
    void updateMessage(const std::string& message);

    // 显示/隐藏状态栏
    void show();
    void hide();

private:
    HWND hwnd;
    static constexpr int STATUS_BAR_HEIGHT = 25;
    static constexpr int PADDING = 5;

    // 窗口过程
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    
    // 当前显示的内容
    std::string currentMode;
    std::string currentMessage;

    // 绘制状态栏
    void paint();
    void createFont();
    
    // 字体句柄
    HFONT hFont;
    
    // 获取状态栏位置
    RECT getStatusBarRect() const;
}; 