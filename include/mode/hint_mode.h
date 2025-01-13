#pragma once

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <sdkddkver.h>
#include <windows.h>
#endif

#include "mode_base.h"
#include "../core/ui_automation.h"

class HintMode : public ModeBase {
public:
    explicit HintMode(UIAutomationManager& uiManager);
    ~HintMode() override = default;

    void enter() override;
    void exit() override;
    void handleKey(DWORD key) override;
    std::string getName() const override;

private:
    UIAutomationManager& uiManager;
    std::string currentInput;
    std::map<std::string, std::string> hintMap; // 提示标签到元素ID的映射
    
    void processHintInput(char key);
    bool tryActivateHint();
    void updateHints();
}; 