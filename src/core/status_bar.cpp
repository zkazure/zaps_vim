#include "core/status_bar.h"
#include <map>

namespace {
    const std::map<Mode, std::string> MODE_NAMES = {
        {Mode::NORMAL, "NORMAL"},
        {Mode::INSERT, "INSERT"},
        {Mode::HINT, "HINT"}
    };

    // 窗口类名
    const wchar_t* WINDOW_CLASS_NAME = L"PixelVimStatusBar";
}

StatusBar::StatusBar() : hwnd(nullptr), hFont(nullptr) {}

StatusBar::~StatusBar() {
    if (hFont) {
        DeleteObject(hFont);
    }
    if (hwnd) {
        DestroyWindow(hwnd);
    }
}

bool StatusBar::initialize() {
    // 注册窗口类
    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = WINDOW_CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassExW(&wc)) {
        return false;
    }

    // 创建状态栏窗口
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
    
    hwnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        WINDOW_CLASS_NAME,
        L"Pixel Vim Status",
        WS_POPUP | WS_VISIBLE,
        workArea.left,
        workArea.bottom - STATUS_BAR_HEIGHT,
        workArea.right - workArea.left,
        STATUS_BAR_HEIGHT,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        this
    );

    if (!hwnd) {
        return false;
    }

    createFont();
    return true;
}

void StatusBar::createFont() {
    hFont = CreateFontW(
        16,                    // 高度
        0,                     // 宽度
        0,                     // 角度
        0,                     // 基线角度
        FW_NORMAL,            // 字重
        FALSE,                // 斜体
        FALSE,                // 下划线
        FALSE,                // 删除线
        DEFAULT_CHARSET,      // 字符集
        OUT_DEFAULT_PRECIS,   // 输出精度
        CLIP_DEFAULT_PRECIS,  // 裁剪精度
        DEFAULT_QUALITY,      // 质量
        DEFAULT_PITCH | FF_DONTCARE,  // 间距和字体族
        L"Consolas"           // 字体名
    );
}

void StatusBar::updateMode(Mode mode) {
    auto it = MODE_NAMES.find(mode);
    if (it != MODE_NAMES.end()) {
        currentMode = it->second;
        paint();
    }
}

void StatusBar::updateMessage(const std::string& message) {
    currentMessage = message;
    paint();
}

void StatusBar::show() {
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

void StatusBar::hide() {
    ShowWindow(hwnd, SW_HIDE);
}

RECT StatusBar::getStatusBarRect() const {
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
    RECT rect = {
        workArea.left,
        workArea.bottom - STATUS_BAR_HEIGHT,
        workArea.right,
        workArea.bottom
    };
    return rect;
}

void StatusBar::paint() {
    if (!hwnd) return;

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    
    // 设置背景色
    SetBkColor(hdc, RGB(40, 40, 40));
    SetTextColor(hdc, RGB(220, 220, 220));
    
    // 选择字体
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
    
    // 获取客户区大小
    RECT rect;
    GetClientRect(hwnd, &rect);
    
    // 填充背景
    HBRUSH hBrush = CreateSolidBrush(RGB(40, 40, 40));
    FillRect(hdc, &rect, hBrush);
    DeleteObject(hBrush);
    
    // 绘制模式文本
    std::string text = currentMode;
    if (!currentMessage.empty()) {
        text += " | " + currentMessage;
    }
    
    rect.left += PADDING;
    DrawTextA(hdc, text.c_str(), -1, &rect, DT_SINGLELINE | DT_VCENTER);
    
    // 恢复原来的字体
    SelectObject(hdc, oldFont);
    
    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK StatusBar::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    StatusBar* statusBar = nullptr;
    
    if (uMsg == WM_CREATE) {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        statusBar = reinterpret_cast<StatusBar*>(cs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(statusBar));
    } else {
        statusBar = reinterpret_cast<StatusBar*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    
    switch (uMsg) {
        case WM_PAINT:
            if (statusBar) {
                statusBar->paint();
            }
            return 0;
            
        case WM_ERASEBKGND:
            return 1;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
} 