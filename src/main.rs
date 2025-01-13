use std::ptr::null_mut;
use winapi::shared::windef::HHOOK;
use crate::keyboard::KEYBOARD_MANAGER;
use crate::window::Direction;

// 引入我们自己定义的模块
mod mode;        // 模式管理
mod keyboard;    // 键盘处理
mod window;      // 窗口管理
mod indicator;   // 状态指示器
mod debug;

// 主程序入口点
fn main() {
    println!("Pixel-vim 启动中...");
    
    // 初始化日志，设置为 debug 级别以显示详细信息
    env_logger::Builder::from_env(env_logger::Env::default().default_filter_or("debug"))
        .init();
    
    // 创建并运行程序
    let mut app = PixelVim::new();
    
    println!("按 Esc 键切换模式");
    println!("按 Alt+H/L 切换窗口");
    println!("按 Ctrl+C 退出程序");
    
    // 运行程序并处理可能的错误
    match app.run() {
        Ok(_) => println!("程序正常退出"),
        Err(e) => eprintln!("程序出错: {}", e),
    }
}

// 主程序结构体
struct PixelVim {
    // 当前模式（Desktop 或 Normal）
    mode: mode::Mode,
    // 键盘钩子句柄（用于监听键盘事件）
    keyboard_hook: HHOOK,
    // 状态指示器（显示当前模式）
    indicator: indicator::StatusIndicator,
}

impl PixelVim {
    // 创建新的程序实例
    fn new() -> Self {
        Self {
            // 默认使用 Desktop 模式启动
            mode: mode::Mode::Desktop,
            // 键盘钩子初始化为空
            keyboard_hook: null_mut(),
            // 创建状态指示器
            indicator: indicator::StatusIndicator::new(),
        }
    }

    // 程序主循环
    fn run(&mut self) -> anyhow::Result<()> {
        // 设置键盘钩子，开始监听键盘事件
        self.setup_keyboard_hook()?;
        
        // 显示状态指示器
        self.indicator.show();
        
        // 消息循环，保持程序运行
        self.message_loop()?;
        
        Ok(())
    }

    fn setup_keyboard_hook(&mut self) -> anyhow::Result<()> {
        use winapi::um::winuser::{
            RegisterHotKey, MOD_ALT,
            SetWindowsHookExW, WH_KEYBOARD_LL,
        };
        use crate::keyboard::{keyboard_hook_proc, KeyboardManager};

        unsafe {
            // 注册 Alt+H 热键
            if RegisterHotKey(std::ptr::null_mut(), 1, MOD_ALT as u32, b'H' as u32) == 0 {
                anyhow::bail!("Failed to register Alt+H hotkey");
            }

            // 注册 Alt+L 热键
            if RegisterHotKey(std::ptr::null_mut(), 2, MOD_ALT as u32, b'L' as u32) == 0 {
                anyhow::bail!("Failed to register Alt+L hotkey");
            }
        }

        // 设置键盘钩子（仍然保留用于 Esc 键）
        let mut keyboard_manager = KeyboardManager::new();
        keyboard_manager.set_indicator(&mut self.indicator);

        unsafe {
            KEYBOARD_MANAGER = Some(keyboard_manager);

            self.keyboard_hook = SetWindowsHookExW(
                WH_KEYBOARD_LL,
                Some(keyboard_hook_proc),
                std::ptr::null_mut(),
                0,
            );

            if self.keyboard_hook.is_null() {
                anyhow::bail!("Failed to set keyboard hook");
            }
        }

        Ok(())
    }

    fn message_loop(&mut self) -> anyhow::Result<()> {
        use winapi::um::winuser::{GetMessageW, MSG, TranslateMessage, DispatchMessageW, WM_HOTKEY};
        
        let mut msg: MSG = unsafe { std::mem::zeroed() };
        
        unsafe {
            while GetMessageW(&mut msg, std::ptr::null_mut(), 0, 0) > 0 {
                if msg.message == WM_HOTKEY {
                    // 处理热键消息
                    match msg.wParam as i32 {
                        1 => { // Alt+H
                            if let Some(manager) = &mut KEYBOARD_MANAGER {
                                manager.get_window_manager().switch_window(Direction::Left);
                            }
                        },
                        2 => { // Alt+L
                            if let Some(manager) = &mut KEYBOARD_MANAGER {
                                manager.get_window_manager().switch_window(Direction::Right);
                            }
                        },
                        _ => {}
                    }
                } else {
                    TranslateMessage(&msg);
                    DispatchMessageW(&msg);
                }
            }
        }

        Ok(())
    }

    // 添加清理方法
    fn cleanup(&mut self) {
        use winapi::um::winuser::{UnhookWindowsHookEx, UnregisterHotKey};
        
        unsafe {
            // 注销热键
            UnregisterHotKey(std::ptr::null_mut(), 1);
            UnregisterHotKey(std::ptr::null_mut(), 2);

            // 清理钩子
            if !self.keyboard_hook.is_null() {
                UnhookWindowsHookEx(self.keyboard_hook);
                self.keyboard_hook = std::ptr::null_mut();
            }
        }
    }
}

// 实现 Drop trait 以确保资源被正确清理
impl Drop for PixelVim {
    fn drop(&mut self) {
        self.cleanup();
    }
}
