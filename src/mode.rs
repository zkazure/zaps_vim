/// 定义程序的工作模式
/// 程序可以在不同的模式下工作，每种模式有不同的按键行为
#[derive(Debug, Clone)]
pub enum Mode {
    /// 桌面模式
    /// 在此模式下，程序主要处理窗口切换等系统级操作
    Desktop,

    /// 普通模式
    /// 在此模式下，程序可以处理文本编辑等操作（待实现）
    Normal,
}

/// 模式管理器
/// 负责处理模式的切换和状态维护
pub struct ModeManager {
    /// 当前的工作模式
    current_mode: Mode,
}

impl ModeManager {
    /// 创建新的模式管理器实例
    /// 默认使用桌面模式启动
    pub fn new() -> Self {
        Self {
            current_mode: Mode::Desktop,
        }
    }

    /// 切换模式
    /// 在 Desktop 和 Normal 模式之间切换
    /// 每次切换时会记录日志以便调试
    pub fn toggle_mode(&mut self) {
        // 根据当前模式切换到另一个模式
        self.current_mode = match self.current_mode {
            Mode::Desktop => Mode::Normal,
            Mode::Normal => Mode::Desktop,
        };
        
        // 记录模式切换的日志
        log::info!("模式切换到: {:?}", self.current_mode);
    }

    /// 获取当前模式
    /// 返回对当前模式的引用
    pub fn current_mode(&self) -> &Mode {
        &self.current_mode
    }
} 