#pragma once
#include "mode_base.h"
#include "../core/ui_automation.h"

class NormalMode : public ModeBase {
public:
    NormalMode(UIAutomationManager& uiManager);
    ~NormalMode() override = default;

    void enter() override;
    void exit() override;
    void handleKey(DWORD key) override;
    std::string getName() const override;

private:
    UIAutomationManager& uiManager;
    void handleNavigation(DWORD key);
    void handleEditing(DWORD key);
    void handleCommand(DWORD key);
}; 