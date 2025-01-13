// This chatgpt working

#include <windows.h>
#include <iostream>
#include <string>

// 函数声明
void simulateKeyPress(WORD key);
void processHotkeys();

// 主程序
int main() {
    while (true) {
        // 每次循环检查按键状态
        processHotkeys();
        Sleep(10);  // 防止过于频繁地占用 CPU 资源
    }
    return 0;
}

// 处理热键逻辑
void processHotkeys() {
    // 获取 CapsLock 键的状态
    if (GetAsyncKeyState(VK_CAPITAL) & 0x8000) {
        // CapsLock 按下时执行某些操作
        std::cout << "CapsLock Pressed" << std::endl;

        // 模拟按下箭头键（如k对应向上，j对应向下）
        if (GetAsyncKeyState(0x4B) & 0x8000) { // k 键
            simulateKeyPress(VK_UP);
        }
        else if (GetAsyncKeyState(0x4A) & 0x8000) { // j 键
            simulateKeyPress(VK_DOWN);
        }
        else if (GetAsyncKeyState(0x48) & 0x8000) { // h 键
            simulateKeyPress(VK_LEFT);
        }
        else if (GetAsyncKeyState(0x4C) & 0x8000) { // l 键
            simulateKeyPress(VK_RIGHT);
        }
        else if (GetAsyncKeyState(0x5B) & 0x8000) { // [ 键
            simulateKeyPress(VK_ESCAPE);
        }
        else if (GetAsyncKeyState(0x20) & 0x8000) { // 空格键
            simulateKeyPress(VK_RETURN);
        }
    }

    // 检查组合键 Ctrl + Enter
    if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_RETURN) & 0x8000)) {
        std::cout << "Ctrl + Enter pressed" << std::endl;
        simulateKeyPress(VK_RETURN);
    }

    // 检查 Shift + CapsLock
    if ((GetAsyncKeyState(VK_SHIFT) & 0x8000) && (GetAsyncKeyState(VK_CAPITAL) & 0x8000)) {
        std::cout << "Shift + CapsLock pressed" << std::endl;
    }
}

// 模拟按键事件
void simulateKeyPress(WORD key) {
    keybd_event(0, MapVirtualKey(key, 0), KEYEVENTF_SCANCODE, 0); // 按下
    keybd_event(0, MapVirtualKey(key, 0), KEYEVENTF_KEYUP, 0); // 松开
}
