#pragma once
#include "mode_base.h"

class InsertMode : public ModeBase {
public:
    InsertMode();
    ~InsertMode() override = default;

    void enter() override;
    void exit() override;
    void handleKey(DWORD key) override;
    std::string getName() const override;

private:
    bool isEscapePressed;
}; 