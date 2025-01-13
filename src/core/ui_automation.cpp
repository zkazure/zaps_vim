#include "core/ui_automation.h"
#include <sstream>

UIAutomationManager::UIAutomationManager() : automation(nullptr) {
}

UIAutomationManager::~UIAutomationManager() {
    if (automation) {
        automation->Release();
    }
    CoUninitialize();
}

bool UIAutomationManager::initialize() {
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        return false;
    }

    hr = CoCreateInstance(__uuidof(CUIAutomation), NULL,
                         CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation),
                         (void**)&automation);
    return SUCCEEDED(hr);
}

std::vector<UIElement> UIAutomationManager::getClickableElements() {
    std::vector<UIElement> result;
    elements.clear();

    IUIAutomationElement* root = nullptr;
    HRESULT hr = automation->GetRootElement(&root);
    if (SUCCEEDED(hr)) {
        collectElements(root);
        root->Release();
    }

    for (const auto& pair : elements) {
        result.push_back(pair.second);
    }
    return result;
}

bool UIAutomationManager::clickElement(const std::string& elementId) {
    auto it = elements.find(elementId);
    if (it == elements.end()) {
        return false;
    }

    const UIElement& element = it->second;
    return clickPosition(
        element.bounds.left + (element.bounds.right - element.bounds.left) / 2,
        element.bounds.top + (element.bounds.bottom - element.bounds.top) / 2
    );
}

bool UIAutomationManager::clickPosition(int x, int y) {
    INPUT input[3] = {0};
    
    // 移动鼠标
    input[0].type = INPUT_MOUSE;
    input[0].mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
    input[0].mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
    input[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;

    // 按下左键
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    // 释放左键
    input[2].type = INPUT_MOUSE;
    input[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    return SendInput(3, input, sizeof(INPUT)) == 3;
}

void UIAutomationManager::showHints() {
    int index = 0;
    for (const auto& pair : elements) {
        std::string hint = generateHintLabel(index++);
        drawHint(pair.second, hint);
    }
}

void UIAutomationManager::hideHints() {
    // 刷新屏幕，清除提示
    InvalidateRect(NULL, NULL, TRUE);
}

// 私有辅助方法

void UIAutomationManager::collectElements(IUIAutomationElement* element) {
    if (!element) return;

    VARIANT_BOOL isClickable;
    IUIAutomationInvokePattern* invokePattern = nullptr;
    if (SUCCEEDED(element->GetCurrentPattern(UIA_InvokePatternId, (IUnknown**)&invokePattern))) {
        isClickable = VARIANT_TRUE;
        invokePattern->Release();
    }

    if (isClickable) {
        UIElement uiElement;
        BSTR name;
        if (SUCCEEDED(element->get_CurrentName(&name))) {
            uiElement.name = _bstr_t(name);
            SysFreeString(name);
        }

        RECT bounds;
        element->get_CurrentBoundingRectangle(&bounds);
        uiElement.bounds = bounds;
        uiElement.clickable = true;

        static int elementCount = 0;
        std::stringstream ss;
        ss << "element_" << elementCount++;
        uiElement.id = ss.str();

        elements[uiElement.id] = uiElement;
    }

    // 递归处理子元素
    IUIAutomationTreeWalker* walker;
    automation->get_RawViewWalker(&walker);
    
    IUIAutomationElement* child;
    walker->GetFirstChildElement(element, &child);
    while (child) {
        collectElements(child);
        IUIAutomationElement* next;
        walker->GetNextSiblingElement(child, &next);
        child->Release();
        child = next;
    }
    
    walker->Release();
}

std::string UIAutomationManager::generateHintLabel(int index) {
    // 生成类似Vimium的提示标签（aa, ab, ac, ...）
    std::string result;
    do {
        result = (char)('a' + (index % 26)) + result;
        index /= 26;
    } while (index > 0);
    return result;
}

void UIAutomationManager::drawHint(const UIElement& element, const std::string& hint) {
    HDC hdc = GetDC(NULL);
    
    // 设置文本样式
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 0, 0));
    
    // 绘制提示文本
    RECT rect = element.bounds;
    DrawText(hdc, hint.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    ReleaseDC(NULL, hdc);
} 