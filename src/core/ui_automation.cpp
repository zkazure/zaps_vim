#include "core/ui_automation.h"
#include <comutil.h>

// 定义CLSID和IID
DEFINE_GUID(CLSID_CUIAutomation, 0xff48dba4, 0x60ef, 0x4201, 0xaa, 0x87, 0x54, 0x10, 0x3e, 0xef, 0x59, 0x4e);
DEFINE_GUID(IID_IUIAutomation, 0x30cbe57d, 0xd9d0, 0x452a, 0xab, 0x13, 0x7a, 0xc5, 0xac, 0x48, 0x25, 0xee);

UIAutomationManager::UIAutomationManager() : 
    automation(nullptr),
    modeManager(std::make_unique<ModeManager>()),
    statusBar(std::make_unique<StatusBar>()) {
    modeManager->registerModeChangeCallback([this](Mode mode) { onModeChanged(mode); });
}

UIAutomationManager::~UIAutomationManager() {
    if (automation) {
        automation->Release();
    }
    CoUninitialize();
}

bool UIAutomationManager::initialize() {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr)) return false;

    hr = CoCreateInstance(CLSID_CUIAutomation, nullptr,
                         CLSCTX_INPROC_SERVER, IID_IUIAutomation,
                         reinterpret_cast<void**>(&automation));
    
    if (FAILED(hr)) {
        CoUninitialize();
        return false;
    }

    return true;
}

void UIAutomationManager::collectElements(struct IUIAutomationElement* element) {
    if (!element) return;

    struct IUIAutomationInvokePattern* invokePattern = nullptr;
    HRESULT hr = element->GetCurrentPattern(UIA_InvokePatternId, 
                                          reinterpret_cast<IUnknown**>(&invokePattern));
    
    if (SUCCEEDED(hr) && invokePattern) {
        BSTR name = nullptr;
        RECT bounds = {};
        
        if (SUCCEEDED(element->get_CurrentName(&name))) {
            if (name) {
                char* elementName = _com_util::ConvertBSTRToString(name);
                if (elementName) {
                    if (SUCCEEDED(element->get_CurrentBoundingRectangle(&bounds))) {
                        UIElement uiElement;
                        uiElement.id = generateHintLabel(elements.size());
                        uiElement.name = elementName;
                        uiElement.bounds = bounds;
                        uiElement.clickable = true;
                        
                        elements[uiElement.id] = uiElement;
                    }
                    delete[] elementName;
                }
                SysFreeString(name);
            }
        }
        invokePattern->Release();
    }

    // 遍历子元素
    struct IUIAutomationTreeWalker* walker = nullptr;
    if (SUCCEEDED(automation->get_RawViewWalker(&walker)) && walker) {
        struct IUIAutomationElement* child = nullptr;
        if (SUCCEEDED(walker->GetFirstChildElement(element, &child)) && child) {
            do {
                collectElements(child);
                
                struct IUIAutomationElement* next = nullptr;
                if (SUCCEEDED(walker->GetNextSiblingElement(child, &next))) {
                    child->Release();
                    child = next;
                } else {
                    child->Release();
                    break;
                }
            } while (child);
        }
        walker->Release();
    }
}

std::vector<UIElement> UIAutomationManager::getClickableElements() {
    elements.clear();
    
    struct IUIAutomationElement* root = nullptr;
    HRESULT hr = automation->GetRootElement(&root);
    
    if (SUCCEEDED(hr) && root) {
        collectElements(root);
        root->Release();
    }
    
    std::vector<UIElement> result;
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
        const UIElement& element = pair.second;
        std::string hint = generateHintLabel(index++);
        drawHint(element, hint);
    }
}

void UIAutomationManager::hideHints() {
    // 重绘屏幕以清除所有提示
    InvalidateRect(NULL, NULL, TRUE);
    UpdateWindow(GetForegroundWindow());
}

std::string UIAutomationManager::generateHintLabel(int index) {
    std::string result;
    do {
        result = (char)('a' + (index % 26)) + result;
        index /= 26;
    } while (index > 0);
    return result;
}

void UIAutomationManager::drawHint(const UIElement& element, const std::string& hint) {
    int len = MultiByteToWideChar(CP_UTF8, 0, hint.c_str(), -1, nullptr, 0);
    if (len <= 0) return;

    wchar_t* wHint = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, hint.c_str(), -1, wHint, len);

    HWND hWnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT,
        L"STATIC",
        wHint,
        WS_POPUP | WS_VISIBLE | SS_CENTER,
        element.bounds.left,
        element.bounds.top,
        30,  // 固定宽度
        20,  // 固定高度
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );

    delete[] wHint;

    if (hWnd) {
        SetLayeredWindowAttributes(hWnd, 0, 200, LWA_ALPHA);
        HDC hdc = GetDC(hWnd);
        SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(255, 255, 255));
        ReleaseDC(hWnd, hdc);
    }
}

bool UIAutomationManager::handleKeyEvent(WPARAM key, bool isKeyDown) {
    return modeManager->handleKeyEvent(key, isKeyDown);
}

Mode UIAutomationManager::getCurrentMode() const {
    return modeManager->getCurrentMode();
}

void UIAutomationManager::onModeChanged(Mode newMode) {
    switch (newMode) {
        case Mode::HINT:
            showHints();
            statusBar->updateMode(newMode);
            break;
        case Mode::NORMAL:
            hideHints();
            statusBar->updateMode(newMode);
            break;
        case Mode::INSERT:
            hideHints();
            statusBar->updateMode(newMode);
            break;
    }
}

void UIAutomationManager::showStatusMessage(const std::string& message) {
    if (statusBar) {
        statusBar->updateMessage(message);
    }
} 