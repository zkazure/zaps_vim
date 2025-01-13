#pragma once
#include <string>
#include <map>

class ConfigLoader {
public:
    ConfigLoader();
    ~ConfigLoader();

    bool loadConfigs();
    std::map<std::string, std::string> getKeymap();
    std::map<std::string, std::string> getSettings();

private:
    std::string configPath;
    std::map<std::string, std::string> keymap;
    std::map<std::string, std::string> settings;

    bool loadKeymap();
    bool loadSettings();
}; 