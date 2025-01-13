#pragma once

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <sdkddkver.h>
#include <windows.h>
#include <UIAutomation.h>
#else
#include <windef.h>
#include <winuser.h>
// Wine下UI自动化的替代定义
typedef void* IUIAutomation;
typedef void* IUIAutomationElement;
#endif

#include <string>
#include <vector>
#include <map>

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

    // 初始化UI自动化
    bool initialize();
    
    // 获取可点击元素
    std::vector<UIElement> getClickableElements();
    
    // 点击操作
    bool clickElement(const std::string& elementId);
    bool clickPosition(int x, int y);
    
    // 提示标签显示
    void showHints();
    void hideHints();

private:
    IUIAutomation* automation;
    std::map<std::string, UIElement> elements;
    
    // 辅助方法
    void collectElements(IUIAutomationElement* element);
    std::string generateHintLabel(int index);
    void drawHint(const UIElement& element, const std::string& hint);
}; 