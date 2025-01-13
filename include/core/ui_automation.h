#pragma once

// 首先定义所有需要的宏
#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// 解决new关键字冲突
#ifdef new
#undef new
#endif

// 基础Windows头文件
#include <windows.h>
#include <objbase.h>
#include <oleauto.h>

// UI Automation接口定义
#include <UIAutomationClient.h>

// 标准库头文件
#include <string>
#include <vector>
#include <map>
#include <memory>

// 项目头文件
#include "core/mode_manager.h"
#include "core/status_bar.h"

struct UIElement {
    std::string id;
    std::string name;
    RECT bounds;
    bool clickable;
};

class UIAutomationManager {
public:
    UIAutomationManager();
    ~UIAutomationManager();

    bool initialize();
    std::vector<UIElement> getClickableElements();
    bool clickElement(const std::string& elementId);
    bool clickPosition(int x, int y);
    void showHints();
    void hideHints();
    bool handleKeyEvent(WPARAM key, bool isKeyDown);
    Mode getCurrentMode() const;
    void showStatusMessage(const std::string& message);

private:
    struct IUIAutomation* automation;
    std::map<std::string, UIElement> elements;
    std::unique_ptr<ModeManager> modeManager;
    std::unique_ptr<StatusBar> statusBar;
    
    void collectElements(struct IUIAutomationElement* element);
    std::string generateHintLabel(int index);
    void drawHint(const UIElement& element, const std::string& hint);
    void onModeChanged(Mode newMode);
}; 