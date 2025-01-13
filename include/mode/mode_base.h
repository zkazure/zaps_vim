#pragma once

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <sdkddkver.h>
#include <windows.h>
#endif

#include <string>

class ModeBase {
public:
    virtual ~ModeBase() = default;
    
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void handleKey(DWORD key) = 0;
    
    virtual std::string getName() const = 0;
}; 