#include "core/mode_manager.h"

ModeManager::ModeManager() 
    : currentMode(Mode::NORMAL)
    , isControlPressed(false)
    , isShiftPressed(false)
    , currentOperator(Operator::NONE)
    , currentTextObject(TextObject::NONE) {
    // 初始化字符查找状态
    findState.target = 0;
    findState.isForward = true;
    findState.isTillMode = false;
    findState.hasLastFind = false;
}

ModeManager::~ModeManager() {}

void ModeManager::switchMode(Mode newMode) {
    if (currentMode != newMode) {
        currentMode = newMode;
        pendingKeys.clear();  // 切换模式时清除待处理的按键
        if (onModeChange) {
            onModeChange(currentMode);
        }
    }
}

Mode ModeManager::getCurrentMode() const {
    return currentMode;
}

void ModeManager::registerModeChangeCallback(ModeChangeCallback callback) {
    onModeChange = callback;
}

void ModeManager::registerActionCallback(ActionCallback callback) {
    onAction = callback;
}

void ModeManager::updateModifierState(WPARAM key, bool isKeyDown) {
    switch (key) {
        case VK_CONTROL:
            isControlPressed = isKeyDown;
            break;
        case VK_SHIFT:
            isShiftPressed = isKeyDown;
            break;
    }
}

bool ModeManager::handleKeyEvent(WPARAM key, bool isKeyDown) {
    updateModifierState(key, isKeyDown);
    
    if (!isKeyDown) return false;

    switch (currentMode) {
        case Mode::NORMAL:
            return handleNormalModeKey(key, isKeyDown);
        case Mode::INSERT:
            return handleInsertModeKey(key, isKeyDown);
        case Mode::HINT:
            return handleHintModeKey(key, isKeyDown);
        case Mode::VISUAL:
            return handleVisualModeKey(key, isKeyDown);
        case Mode::OPERATOR_PENDING:
            return handleOperatorPendingKey(key, isKeyDown);
        case Mode::FIND_PENDING:
            return handleFindChar(key, isKeyDown);
        default:
            return false;
    }
}

void ModeManager::executeAction(Action action) {
    if (onAction) {
        onAction(action);
    }
}

bool ModeManager::handleMultiKeyCommand() {
    if (pendingKeys == "gg") {  // 跳转到文件开头
        executeAction(Action::PAGE_UP);
        pendingKeys.clear();
        return true;
    }
    else if (pendingKeys == "G") {  // 跳转到文件末尾
        executeAction(Action::PAGE_DOWN);
        pendingKeys.clear();
        return true;
    }
    else if (pendingKeys == "dd") {  // 删除当前行
        executeAction(Action::DEL_LINE);
        pendingKeys.clear();
        return true;
    }
    else if (pendingKeys == "yy") {  // 复制当前行
        executeAction(Action::YANK_LINE);
        pendingKeys.clear();
        return true;
    }
    // 如果命令不完整，继续等待更多按键
    return false;
}

bool ModeManager::handleOperator(WPARAM key) {
    switch (key) {
        case 'D':
            currentOperator = Operator::DEL;
            break;
        case 'C':
            currentOperator = Operator::CHANGE;
            break;
        case 'Y':
            currentOperator = Operator::YANK;
            break;
        case '>':
            currentOperator = Operator::INDENT;
            break;
        case '<':
            currentOperator = Operator::UNINDENT;
            break;
        default:
            return false;
    }
    switchMode(Mode::OPERATOR_PENDING);
    return true;
}

bool ModeManager::handleTextObject(WPARAM key) {
    switch (key) {
        case 'W':
            currentTextObject = TextObject::WORD;
            break;
        case 'S':
            currentTextObject = TextObject::SENTENCE;
            break;
        case 'P':
            currentTextObject = TextObject::PARAGRAPH;
            break;
        case '(':
        case ')':
            currentTextObject = TextObject::PARENTHESES;
            break;
        case '[':
        case ']':
            currentTextObject = TextObject::BRACKETS;
            break;
        case '{':
        case '}':
            currentTextObject = TextObject::BRACES;
            break;
        case '"':
            currentTextObject = TextObject::QUOTES;
            break;
        case '\'':
            currentTextObject = TextObject::SINGLE_QUOTES;
            break;
        case '`':
            currentTextObject = TextObject::BACKTICKS;
            break;
        case '<':
        case '>':
            currentTextObject = TextObject::TAG;
            break;
        default:
            return false;
    }
    executeOperatorAction();
    return true;
}

void ModeManager::executeOperatorAction() {
    Action action = Action::ACTION_NONE;
    
    switch (currentOperator) {
        case Operator::DEL:
            switch (currentTextObject) {
                case TextObject::WORD:
                    action = Action::DEL_WORD;
                    break;
                case TextObject::NONE:
                    action = Action::DEL_LINE;
                    break;
                default:
                    action = Action::DEL_INSIDE;
                    break;
            }
            break;
            
        case Operator::CHANGE:
            switch (currentTextObject) {
                case TextObject::WORD:
                    action = Action::CHANGE_WORD;
                    break;
                case TextObject::NONE:
                    action = Action::CHANGE_LINE;
                    break;
                default:
                    action = Action::CHANGE_INSIDE;
                    break;
            }
            break;
            
        case Operator::YANK:
            switch (currentTextObject) {
                case TextObject::WORD:
                    action = Action::YANK_WORD;
                    break;
                case TextObject::NONE:
                    action = Action::YANK_LINE;
                    break;
                default:
                    action = Action::YANK_INSIDE;
                    break;
            }
            break;
            
        case Operator::INDENT:
            action = Action::INDENT_RIGHT;
            break;
            
        case Operator::UNINDENT:
            action = Action::INDENT_LEFT;
            break;
    }
    
    if (action != Action::ACTION_NONE) {
        executeAction(action);
    }
    
    // 重置状态
    currentOperator = Operator::NONE;
    currentTextObject = TextObject::NONE;
    switchMode(Mode::NORMAL);
}

bool ModeManager::handleOperatorPendingKey(WPARAM key, bool isKeyDown) {
    if (key == VK_ESCAPE) {
        currentOperator = Operator::NONE;
        switchMode(Mode::NORMAL);
        return true;
    }

    // 处理文本对象
    if (handleTextObject(key)) {
        return true;
    }

    // 处理重复操作符（如 dd, yy）
    if ((char)key == (char)pendingKeys[0]) {
        currentTextObject = TextObject::NONE;
        executeOperatorAction();
        return true;
    }

    return false;
}

bool ModeManager::handleNormalModeKey(WPARAM key, bool isKeyDown) {
    // 处理修饰键组合
    if (isControlPressed) {
        switch (key) {
            case 'U':  // Ctrl+U: 向上翻页
                executeAction(Action::PAGE_UP);
                return true;
            case 'D':  // Ctrl+D: 向下翻页
                executeAction(Action::PAGE_DOWN);
                return true;
            case 'R':  // Ctrl+R: 重做
                executeAction(Action::REDO);
                return true;
            case 'J':  // Ctrl+J: 合并行
                executeAction(Action::JOIN_LINES);
                return true;
        }
        return false;
    }

    // 处理特殊移动命令
    if (handleSpecialMovement(key)) {
        return true;
    }

    // 处理操作符
    if (handleOperator(key)) {
        return true;
    }

    // 处理其他命令
    switch (key) {
        case 'H':  // 左移
            executeAction(Action::MOVE_LEFT);
            return true;
        case 'J':  // 下移
            executeAction(Action::MOVE_DOWN);
            return true;
        case 'K':  // 上移
            executeAction(Action::MOVE_UP);
            return true;
        case 'L':  // 右移
            executeAction(Action::MOVE_RIGHT);
            return true;
        case 'I':  // 切换到Insert模式
            switchMode(Mode::INSERT);
            return true;
        case 'V':  // 切换到Visual模式
            switchMode(Mode::VISUAL);
            return true;
        case 'W':  // 下一个词
            executeAction(Action::WORD_NEXT);
            return true;
        case 'B':  // 上一个词
            executeAction(Action::WORD_PREV);
            return true;
        case 'N':  // 查找下一个
            executeAction(Action::FIND_NEXT);
            return true;
        case 'P':  // 粘贴
            executeAction(Action::PASTE);
            return true;
        case '0':  // 行首
            executeAction(Action::LINE_START);
            return true;
        case '$':  // 行尾
            executeAction(Action::LINE_END);
            return true;
        case 'U':  // 撤销
            executeAction(Action::UNDO);
            return true;
        case 'R':  // 替换模式
            executeAction(Action::REPLACE_MODE);
            return true;
        case 'r':  // 替换字符
            executeAction(Action::REPLACE_CHAR);
            return true;
        case '/':  // 向前搜索
            executeAction(Action::SEARCH_FORWARD);
            return true;
        case '?':  // 向后搜索
            executeAction(Action::SEARCH_BACKWARD);
            return true;
        case '`':  // 跳转到标记
            executeAction(Action::GOTO_MARK);
            return true;
        case 'm':  // 设置标记
            executeAction(Action::SET_MARK);
            return true;
        case 'f':  // 向前查找字符
            findState.isForward = true;
            findState.isTillMode = false;
            switchMode(Mode::FIND_PENDING);
            return true;
        case 't':  // 向前till字符
            findState.isForward = true;
            findState.isTillMode = true;
            switchMode(Mode::FIND_PENDING);
            return true;
        case 'T':  // 向后till字符
            findState.isForward = false;
            findState.isTillMode = true;
            switchMode(Mode::FIND_PENDING);
            return true;
        case ';':  // 重复上次查找
            if (findState.hasLastFind) {
                executeFindAction();
                return true;
            }
            return false;
        case ',':  // 反向重复上次查找
            if (findState.hasLastFind) {
                findState.isForward = !findState.isForward;
                executeFindAction();
                findState.isForward = !findState.isForward;
                return true;
            }
            return false;
        case 'a':  // 在光标后追加
            executeAction(Action::APPEND);
            switchMode(Mode::INSERT);
            return true;
        case 'A':  // 在行尾追加
            executeAction(Action::APPEND_EOL);
            switchMode(Mode::INSERT);
            return true;
        case 'o':  // 在下方打开新行
            executeAction(Action::OPEN_LINE_BELOW);
            switchMode(Mode::INSERT);
            return true;
        case 'O':  // 在上方打开新行
            executeAction(Action::OPEN_LINE_ABOVE);
            switchMode(Mode::INSERT);
            return true;
        case 'S':  // 替换整行
            executeAction(Action::REPLACE_LINE);
            switchMode(Mode::INSERT);
            return true;
        case 'x':  // 删除光标下的字符
            executeAction(Action::DEL_CHAR_FORWARD);
            return true;
        case 'X':  // 删除光标前的字符
            executeAction(Action::DEL_CHAR_BACKWARD);
            return true;
    }

    // 处理需要修饰键的命令
    if (isShiftPressed) {
        switch (key) {
            case 'F':  // Shift+F: 向后查找字符
                findState.isForward = false;
                findState.isTillMode = false;
                switchMode(Mode::FIND_PENDING);
                return true;
        }
    } else {
        switch (key) {
            case 'F':  // f: 切换到Hint模式
                switchMode(Mode::HINT);
                return true;
        }
    }

    return false;
}

bool ModeManager::handleInsertModeKey(WPARAM key, bool isKeyDown) {
    if (key == VK_ESCAPE) {  // ESC键返回Normal模式
        switchMode(Mode::NORMAL);
        return true;
    }
    
    // 在Insert模式下，只处理Ctrl+S保存
    if (isControlPressed && key == 'S') {
        executeAction(Action::SAVE);
        return true;
    }
    
    return false;  // 其他按键传递给系统
}

bool ModeManager::handleHintModeKey(WPARAM key, bool isKeyDown) {
    if (key == VK_ESCAPE) {  // ESC键返回Normal模式
        switchMode(Mode::NORMAL);
        return true;
    }
    
    // 字母键用于选择提示
    if (key >= 'A' && key <= 'Z') {
        // TODO: 处理提示选择
        switchMode(Mode::NORMAL);
        return true;
    }
    
    return false;
}

bool ModeManager::handleVisualModeKey(WPARAM key, bool isKeyDown) {
    if (key == VK_ESCAPE) {  // ESC键返回Normal模式
        switchMode(Mode::NORMAL);
        return true;
    }

    // 在Visual模式下支持和Normal模式相同的移动命令
    switch (key) {
        case 'H':
            executeAction(Action::MOVE_LEFT);
            return true;
        case 'J':
            executeAction(Action::MOVE_DOWN);
            return true;
        case 'K':
            executeAction(Action::MOVE_UP);
            return true;
        case 'L':
            executeAction(Action::MOVE_RIGHT);
            return true;
        case 'Y':  // 复制选中内容
            executeAction(Action::COPY);
            switchMode(Mode::NORMAL);
            return true;
        case 'D':  // 剪切选中内容
            executeAction(Action::CUT);
            switchMode(Mode::NORMAL);
            return true;
    }

    return false;
}

bool ModeManager::handleFindChar(WPARAM key, bool isKeyDown) {
    if (key == VK_ESCAPE) {
        switchMode(Mode::NORMAL);
        return true;
    }

    // 记录查找目标字符
    findState.target = (char)key;
    findState.hasLastFind = true;
    
    // 执行查找动作
    executeFindAction();
    
    // 返回到Normal模式
    switchMode(Mode::NORMAL);
    return true;
}

void ModeManager::executeFindAction() {
    if (findState.isForward) {
        executeAction(findState.isTillMode ? Action::TILL_CHAR_FORWARD : Action::FIND_CHAR_FORWARD);
    } else {
        executeAction(findState.isTillMode ? Action::TILL_CHAR_BACKWARD : Action::FIND_CHAR_BACKWARD);
    }
}

bool ModeManager::handleSpecialMovement(WPARAM key) {
    switch (key) {
        case '{':
            executeAction(Action::MOVE_PARAGRAPH_UP);
            return true;
        case '}':
            executeAction(Action::MOVE_PARAGRAPH_DOWN);
            return true;
        case 'H':
            if (isShiftPressed) {
                executeAction(Action::MOVE_SCREEN_TOP);
                return true;
            }
            break;
        case 'M':
            if (isShiftPressed) {
                executeAction(Action::MOVE_SCREEN_MIDDLE);
                return true;
            }
            break;
        case 'L':
            if (isShiftPressed) {
                executeAction(Action::MOVE_SCREEN_BOTTOM);
                return true;
            }
            break;
        case '%':
            executeAction(Action::MOVE_MATCHING_PAIR);
            return true;
    }
    return false;
} 