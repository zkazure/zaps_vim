// 定义程序的模式
#[derive(Debug, PartialEq)]
pub enum Mode {
    // 桌面模式，用于系统级操作
    Desktop,
    // 普通模式，用于文本编辑
    Normal,
}

// 模式管理器
pub struct ModeManager {
    // 当前的模式
    current_mode: Mode,
}

impl ModeManager {
    // 创建新的模式管理器
    pub fn new() -> Self {
        Self {
            // 默认使用桌面模式
            current_mode: Mode::Desktop,
        }
    }

    // 切换模式
    pub fn toggle_mode(&mut self) {
        // 在 Desktop 和 Normal 模式之间切换
        self.current_mode = match self.current_mode {
            Mode::Desktop => Mode::Normal,
            Mode::Normal => Mode::Desktop,
        };
        
        // 记录模式切换的日志
        log::info!("模式切换到: {:?}", self.current_mode);
    }

    // 获取当前模式
    pub fn current_mode(&self) -> &Mode {
        &self.current_mode
    }
} 