#include "mode/insert_mode.h"
#include <iostream>

InsertMode::InsertMode() : isEscapePressed(false) {
}

void InsertMode::enter() {
    std::cout << "进入插入模式" << std::endl;
}

void InsertMode::exit() {
    std::cout << "退出插入模式" << std::endl;
}

void InsertMode::handleKey(DWORD key) {
    if (key == VK_ESCAPE) {
        isEscapePressed = true;
        // TODO: 切换回普通模式
        return;
    }

    // 在插入模式下，直接传递按键
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    
    SendInput(1, &input, sizeof(INPUT));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

std::string InsertMode::getName() const {
    return "Insert";
} 