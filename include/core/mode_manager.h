#pragma once

#include <windows.h>
#include <functional>
#include <map>
#include <memory>
#include <string>

enum class Mode {
    NORMAL,
    INSERT,
    HINT,
    VISUAL,
    OPERATOR_PENDING,
    FIND_PENDING
};

// 定义动作类型
enum class Action {
    // 移动命令
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    PAGE_UP,
    PAGE_DOWN,
    LINE_START,
    LINE_END,
    WORD_NEXT,
    WORD_PREV,
    FIND_NEXT,
    FIND_PREV,
    
    // 编辑命令
    COPY,
    PASTE,
    CUT,
    DEL,
    BACKSPACE,
    UNDO,
    REDO,
    SAVE,
    QUIT,
    
    // 新增的动作
    DEL_WORD,
    DEL_LINE,
    DEL_INSIDE,
    DEL_AROUND,
    CHANGE_WORD,
    CHANGE_LINE,
    CHANGE_INSIDE,
    CHANGE_AROUND,
    YANK_WORD,
    YANK_LINE,
    YANK_INSIDE,
    YANK_AROUND,
    INDENT_RIGHT,
    INDENT_LEFT,
    JOIN_LINES,
    REPLACE_CHAR,
    REPLACE_MODE,
    SEARCH_FORWARD,
    SEARCH_BACKWARD,
    GOTO_MARK,
    SET_MARK,
    
    // 新增字符查找动作
    FIND_CHAR_FORWARD,
    FIND_CHAR_BACKWARD,
    TILL_CHAR_FORWARD,
    TILL_CHAR_BACKWARD,
    REPEAT_FIND_FORWARD,
    REPEAT_FIND_BACKWARD,
    
    // 新增移动动作
    MOVE_PARAGRAPH_UP,
    MOVE_PARAGRAPH_DOWN,
    MOVE_SCREEN_TOP,
    MOVE_SCREEN_MIDDLE,
    MOVE_SCREEN_BOTTOM,
    MOVE_MATCHING_PAIR,
    
    // 新增编辑动作
    APPEND,
    APPEND_EOL,
    INSERT_BOL,
    OPEN_LINE_ABOVE,
    OPEN_LINE_BELOW,
    REPLACE_LINE,
    DEL_CHAR_FORWARD,
    DEL_CHAR_BACKWARD,

    ACTION_NONE
};

// 定义操作符类型
enum class Operator {
    NONE,
    DEL,
    CHANGE,
    YANK,
    INDENT,
    UNINDENT
};

// 定义文本对象
enum class TextObject {
    NONE,
    WORD,
    SENTENCE,
    PARAGRAPH,
    PARENTHESES,
    BRACKETS,
    BRACES,
    QUOTES,
    SINGLE_QUOTES,
    BACKTICKS,
    TAG
};

class ModeManager {
public:
    ModeManager();
    ~ModeManager();

    // 模式切换
    void switchMode(Mode newMode);
    Mode getCurrentMode() const;

    // 键盘事件处理
    bool handleKeyEvent(WPARAM key, bool isKeyDown);

    // 注册回调
    using ModeChangeCallback = std::function<void(Mode)>;
    using ActionCallback = std::function<void(Action)>;
    void registerModeChangeCallback(ModeChangeCallback callback);
    void registerActionCallback(ActionCallback callback);

private:
    Mode currentMode;
    ModeChangeCallback onModeChange;
    ActionCallback onAction;
    
    // 记录组合键状态
    bool isControlPressed;
    bool isShiftPressed;
    std::string pendingKeys;  // 用于存储多键命令
    
    // 操作符状态
    Operator currentOperator;
    TextObject currentTextObject;

    // 模式特定的键盘处理
    bool handleNormalModeKey(WPARAM key, bool isKeyDown);
    bool handleInsertModeKey(WPARAM key, bool isKeyDown);
    bool handleHintModeKey(WPARAM key, bool isKeyDown);
    bool handleVisualModeKey(WPARAM key, bool isKeyDown);
    bool handleOperatorPendingKey(WPARAM key, bool isKeyDown);

    // 处理修饰键
    void updateModifierState(WPARAM key, bool isKeyDown);
    
    // 处理动作
    void executeAction(Action action);
    
    // 处理多键命令
    bool handleMultiKeyCommand();
    
    // 处理操作符和文本对象
    bool handleOperator(WPARAM key);
    bool handleTextObject(WPARAM key);
    void executeOperatorAction();

    // 字符查找状态
    struct FindState {
        char target;           // 要查找的字符
        bool isForward;        // 是否向前查找
        bool isTillMode;       // 是否是till模式（t/T vs f/F）
        bool hasLastFind;      // 是否有上次的查找
    } findState;
    
    // 新增的处理方法
    bool handleFindChar(WPARAM key, bool isKeyDown);
    void executeFindAction();
    bool handleSpecialMovement(WPARAM key);
}; 