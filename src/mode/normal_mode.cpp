#include "mode/normal_mode.h"
#include <windows.h>
#include <iostream>

NormalMode::NormalMode() {
}

void NormalMode::enter() {
    std::cout << "进入普通模式" << std::endl;
}

void NormalMode::exit() {
    std::cout << "退出普通模式" << std::endl;
}

void NormalMode::handleKey(DWORD key) {
    switch (key) {
        case 'H': // 左移
        case 'J': // 下移
        case 'K': // 上移
        case 'L': // 右移
            handleNavigation(key);
            break;
        
        case 'I': // 进入插入模式
        case 'A': // 在当前位置后进入插入模式
            // TODO: 切换到插入模式
            break;
        
        case 'D': // 删除操作
        case 'Y': // 复制操作
        case 'P': // 粘贴操作
            handleEditing(key);
            break;
        
        case VK_OEM_2: // 斜杠键，进入搜索
        case VK_OEM_1: // 分号键，进入命令模式
            handleCommand(key);
            break;
        
        case 'F': // 显示点击提示
            handleHintMode();
            break;
    }
}

std::string NormalMode::getName() const {
    return "Normal";
}

void NormalMode::handleNavigation(DWORD key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    
    switch (key) {
        case 'H':
            input.ki.wVk = VK_LEFT;
            break;
        case 'J':
            input.ki.wVk = VK_DOWN;
            break;
        case 'K':
            input.ki.wVk = VK_UP;
            break;
        case 'L':
            input.ki.wVk = VK_RIGHT;
            break;
    }
    
    SendInput(1, &input, sizeof(INPUT));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void NormalMode::handleEditing(DWORD key) {
    switch (key) {
        case 'D':
            // 实现删除功能
            break;
        case 'Y':
            // 实现复制功能
            break;
        case 'P':
            // 实现粘贴功能
            break;
    }
}

void NormalMode::handleCommand(DWORD key) {
    // 处理命令模式切换
}

void NormalMode::handleHintMode() {
    uiAutomation.showHints();
    // 等待用户输入提示标签
    // TODO: 实现提示标签的输入和处理
} 