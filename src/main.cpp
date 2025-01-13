#include <windows.h>
#include <iostream>
#include "mode/mode_manager.h"
#include "core/key_handler.h"
#include "core/window_manager.h"
#include "utils/config_loader.h"

// 全局变量
ModeManager* g_modeManager = nullptr;
KeyHandler* g_keyHandler = nullptr;

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_HOTKEY:
            if (g_keyHandler) {
                g_keyHandler->handleKeyEvent(LOWORD(lParam));
            }
            break;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
            
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main() {
    try {
        // 注册窗口类
        WNDCLASSEX wc = {0};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = L"PixelVimClass";
        RegisterClassEx(&wc);

        // 创建隐藏窗口用于接收消息
        HWND hwnd = CreateWindowEx(
            0, L"PixelVimClass", L"PixelVim",
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            100, 100, NULL, NULL, GetModuleHandle(NULL), NULL
        );

        if (!hwnd) {
            std::cerr << "创建窗口失败" << std::endl;
            return 1;
        }

        std::cout << "Pixel-vim 启动中..." << std::endl;
        
        // 初始化模式管理器
        g_modeManager = new ModeManager();
        
        // 初始化按键处理器
        g_keyHandler = new KeyHandler(g_modeManager);
        
        // 注册全局热键
        if (!g_keyHandler->registerGlobalHotkeys()) {
            std::cerr << "全局热键注册失败" << std::endl;
            return 1;
        }

        std::cout << "Pixel-vim 已启动" << std::endl;
        std::cout << "按键说明：" << std::endl;
        std::cout << "Alt+H/L - 切换窗口" << std::endl;
        std::cout << "Alt+J/K - 切换标签页" << std::endl;
        std::cout << "F      - 显示点击提示" << std::endl;
        std::cout << "ESC    - 返回普通模式" << std::endl;
        std::cout << "Alt+Q  - 退出程序" << std::endl;

        // 消息循环
        MSG msg = {0};
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // 清理资源
        delete g_keyHandler;
        delete g_modeManager;
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "发生错误: " << e.what() << std::endl;
        return 1;
    }
} 