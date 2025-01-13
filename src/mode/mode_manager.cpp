#include "mode/mode_manager.h"
#include "mode/normal_mode.h"
#include "mode/insert_mode.h"
#include "mode/hint_mode.h"
#include <iostream>

ModeManager::ModeManager() : currentMode(nullptr) {
    initModes();
    // 默认进入普通模式
    switchMode("Normal");
}

ModeManager::~ModeManager() {
    for (auto& pair : modes) {
        delete pair.second;
    }
    modes.clear();
}

void ModeManager::initModes() {
    UIAutomationManager* uiManager = new UIAutomationManager();
    if (!uiManager->initialize()) {
        std::cerr << "UI自动化初始化失败" << std::endl;
        delete uiManager;
        return;
    }

    modes["Normal"] = new NormalMode(*uiManager);
    modes["Insert"] = new InsertMode();
    modes["Hint"] = new HintMode(*uiManager);
    
    // 设置默认模式
    currentMode = modes["Normal"];
}

void ModeManager::switchMode(const std::string& modeName) {
    auto it = modes.find(modeName);
    if (it == modes.end()) {
        std::cerr << "未知模式: " << modeName << std::endl;
        return;
    }

    if (currentMode) {
        currentMode->exit();
    }

    currentMode = it->second;
    currentMode->enter();
}

void ModeManager::handleKey(DWORD key) {
    if (currentMode) {
        currentMode->handleKey(key);
    }
}

std::string ModeManager::getCurrentMode() const {
    return currentMode ? currentMode->getName() : "Unknown";
} 