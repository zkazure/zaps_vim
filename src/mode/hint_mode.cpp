#include "mode/hint_mode.h"
#include <iostream>

HintMode::HintMode(UIAutomationManager& uiManager) 
    : uiManager(uiManager), currentInput("") {
}

void HintMode::enter() {
    std::cout << "进入提示模式" << std::endl;
    
    // 获取所有可点击元素并显示提示
    auto elements = uiManager.getClickableElements();
    hintMap.clear();
    
    // 为每个元素生成提示标签
    for (size_t i = 0; i < elements.size(); ++i) {
        std::string hint = uiManager.generateHintLabel(i);
        hintMap[hint] = elements[i].id;
    }
    
    uiManager.showHints();
}

void HintMode::exit() {
    std::cout << "退出提示模式" << std::endl;
    uiManager.hideHints();
    currentInput.clear();
    hintMap.clear();
}

void HintMode::handleKey(DWORD key) {
    // 处理ESC键
    if (key == VK_ESCAPE) {
        exit();
        // TODO: 切换回普通模式
        return;
    }
    
    // 处理退格键
    if (key == VK_BACK) {
        if (!currentInput.empty()) {
            currentInput.pop_back();
            updateHints();
        }
        return;
    }
    
    // 处理字母键
    if (key >= 'A' && key <= 'Z') {
        char c = static_cast<char>(key - 'A' + 'a');
        processHintInput(c);
    }
}

std::string HintMode::getName() const {
    return "Hint";
}

void HintMode::processHintInput(char key) {
    currentInput += key;
    
    // 尝试激活提示
    if (!tryActivateHint()) {
        // 如果没有匹配的提示，更新显示
        updateHints();
    }
}

bool HintMode::tryActivateHint() {
    // 检查是否有完全匹配的提示
    auto it = hintMap.find(currentInput);
    if (it != hintMap.end()) {
        // 找到匹配的提示，执行点击
        if (uiManager.clickElement(it->second)) {
            exit();
            // TODO: 切换回普通模式
            return true;
        }
    }
    
    // 检查是否还有以当前输入为前缀的提示
    bool hasPrefix = false;
    for (const auto& pair : hintMap) {
        if (pair.first.find(currentInput) == 0) {
            hasPrefix = true;
            break;
        }
    }
    
    // 如果没有可能的匹配，清空输入
    if (!hasPrefix) {
        currentInput.clear();
        updateHints();
    }
    
    return false;
}

void HintMode::updateHints() {
    uiManager.hideHints();
    
    // 只显示匹配当前输入的提示
    if (!currentInput.empty()) {
        for (const auto& pair : hintMap) {
            if (pair.first.find(currentInput) == 0) {
                // TODO: 高亮显示匹配的提示
            }
        }
    } else {
        uiManager.showHints();
    }
} 