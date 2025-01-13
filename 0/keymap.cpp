#include "keymap.h"
#include <unordered_map>
#include <string>
#include <windows.h>

// Initialize the key mapping
// create a map of key codes to key names
// the name rules the to capcialize the first letters
std::unordered_map<int, std::string> keyMap = {
    {0x41, "A"}, {0x42, "B"}, {0x43, "C"}, {0x44, "D"}, {0x45, "E"},
    {0x46, "F"}, {0x47, "G"}, {0x48, "H"}, {0x49, "I"}, {0x4A, "J"},
    {0x4B, "K"}, {0x4C, "L"}, {0x4D, "M"}, {0x4E, "N"}, {0x4F, "O"},
    {0x50, "P"}, {0x51, "Q"}, {0x52, "R"}, {0x53, "S"}, {0x54, "T"},
    {0x55, "U"}, {0x56, "V"}, {0x57, "W"}, {0x58, "X"}, {0x59, "Y"},
    {0x5A, "Z"},

    {0x30, "0"}, {0x31, "1"}, {0x32, "2"}, {0x33, "3"}, {0x34, "4"},
    {0x35, "5"}, {0x36, "6"}, {0x37, "7"}, {0x38, "8"}, {0x39, "9"},

    {VK_SPACE, "Space"}, {VK_RETURN, "Enter"}, {VK_ESCAPE, "Escape"},
    {VK_BACK, "Backspace"}, {VK_TAB, "Tab"}, {VK_SHIFT, "Shift"},
    {VK_CONTROL, "Ctrl"}, {VK_MENU, "Alt"}, {VK_CAPITAL, "CapsLock"},

    {VK_UP, "Up"}, {VK_DOWN, "Down"}, {VK_LEFT, "Left"}, {VK_RIGHT, "Right"},

    {VK_INSERT, "Insert"}, {VK_DELETE, "Delete"}, {VK_HOME, "Home"},
    {VK_END, "End"}, {VK_PRIOR, "PageUp"}, {VK_NEXT, "PageDown"},

    {VK_F1, "F1"}, {VK_F2, "F2"}, {VK_F3, "F3"}, {VK_F4, "F4"},
    {VK_F5, "F5"}, {VK_F6, "F6"}, {VK_F7, "F7"}, {VK_F8, "F8"},
    {VK_F9, "F9"}, {VK_F10, "F10"}, {VK_F11, "F11"}, {VK_F12, "F12"},

    {VK_NUMPAD0, "Numpad0"}, {VK_NUMPAD1, "Numpad1"}, {VK_NUMPAD2, "Numpad2"},
    {VK_NUMPAD3, "Numpad3"}, {VK_NUMPAD4, "Numpad4"}, {VK_NUMPAD5, "Numpad5"},
    {VK_NUMPAD6, "Numpad6"}, {VK_NUMPAD7, "Numpad7"}, {VK_NUMPAD8, "Numpad8"},
    {VK_NUMPAD9, "Numpad9"}, {VK_MULTIPLY, "NumpadMultiply"},
    {VK_ADD, "NumpadAdd"}, {VK_SEPARATOR, "NumpadSeparator"},
    {VK_SUBTRACT, "NumpadSubtract"}, {VK_DECIMAL, "NumpadDecimal"},
    {VK_DIVIDE, "NumpadDivide"},

    {VK_OEM_1, "Semicolon"}, // ";"
    {VK_OEM_PLUS, "Equal"}, // "="
    {VK_OEM_COMMA, "Comma"}, // ","
    {VK_OEM_MINUS, "Minus"}, // "-"
    {VK_OEM_PERIOD, "Period"}, // "."
    {VK_OEM_l2, "Slash"}, // "\"
    {VK_OEM_3, "Grave"}, // "`"
    {VK_OEM_4, "Leftbracket"}, // "["
    {VK_OEM_5, "Backslash"}, // "\"
    {VK_OEM_6, "Rightbracket"}, // "]"
    {VK_OEM_7, "Apostrophe"}, // "'"
};
