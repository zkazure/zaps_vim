#include "core/key_handler.h"
#include <iostream>

// 定义全局热键ID
#define HOT_KEY_ALT_H 1
#define HOT_KEY_ALT_L 2
#define HOT_KEY_ALT_J 3
#define HOT_KEY_ALT_K 4
#define HOT_KEY_ALT_Q 5

KeyHandler::KeyHandler(ModeManager* modeManager) 
    : modeManager(modeManager), isAltPressed(false), isCtrlPressed(false) {
}

KeyHandler::~KeyHandler() {
    unregisterGlobalHotkeys();
}

bool KeyHandler::registerGlobalHotkeys() {
    // 注册Alt组合键
    if (!RegisterHotKey(NULL, HOT_KEY_ALT_H, MOD_ALT, 'H') ||
        !RegisterHotKey(NULL, HOT_KEY_ALT_L, MOD_ALT, 'L') ||
        !RegisterHotKey(NULL, HOT_KEY_ALT_J, MOD_ALT, 'J') ||
        !RegisterHotKey(NULL, HOT_KEY_ALT_K, MOD_ALT, 'K') ||
        !RegisterHotKey(NULL, HOT_KEY_ALT_Q, MOD_ALT, 'Q')) {
        
        std::cerr << "注册全局热键失败" << std::endl;
        return false;
    }
    return true;
}

void KeyHandler::unregisterGlobalHotkeys() {
    UnregisterHotKey(NULL, HOT_KEY_ALT_H);
    UnregisterHotKey(NULL, HOT_KEY_ALT_L);
    UnregisterHotKey(NULL, HOT_KEY_ALT_J);
    UnregisterHotKey(NULL, HOT_KEY_ALT_K);
    UnregisterHotKey(NULL, HOT_KEY_ALT_Q);
}

void KeyHandler::handleKeyEvent(DWORD key) {
    // 处理修饰键状态
    if (key == VK_MENU) { // Alt键
        isAltPressed = true;
        return;
    }
    if (key == VK_CONTROL) { // Ctrl键
        isCtrlPressed = true;
        return;
    }

    // 处理热键组合
    if (isAltPressed) {
        switch (key) {
            case 'H':
                switchToPreviousWindow();
                break;
            case 'L':
                switchToNextWindow();
                break;
            case 'J':
                switchToNextTab();
                break;
            case 'K':
                switchToPreviousTab();
                break;
            case 'Q':
                PostQuitMessage(0);
                break;
        }
    } else {
        // 将按键传递给当前模式处理
        modeManager->handleKey(key);
    }
}

// 添加以下私有辅助方法

void KeyHandler::switchToPreviousWindow() {
    windowManager.switchToPreviousWindow();
}

void KeyHandler::switchToNextWindow() {
    windowManager.switchToNextWindow();
}

void KeyHandler::switchToNextTab() {
    // 模拟Ctrl+Tab操作
    INPUT inputs[2] = {0};
    
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;
    
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_TAB;
    
    SendInput(2, inputs, sizeof(INPUT));
}

void KeyHandler::switchToPreviousTab() {
    // 模拟Ctrl+Shift+Tab操作
    INPUT inputs[3] = {0};
    
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;
    
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_SHIFT;
    
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = VK_TAB;
    
    SendInput(3, inputs, sizeof(INPUT));
} 