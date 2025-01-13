#pragma once

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <sdkddkver.h>
#include <windows.h>
#endif

#include <string>
#include <map>
#include "mode_base.h"

class ModeManager {
public:
    ModeManager();
    ~ModeManager();

    void switchMode(const std::string& modeName);
    void handleKey(DWORD key);
    std::string getCurrentMode() const;

private:
    std::map<std::string, ModeBase*> modes;
    ModeBase* currentMode;
    
    void initModes();
}; 