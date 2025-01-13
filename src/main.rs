use std::ptr::null_mut;
use winapi::shared::windef::HHOOK;
use winapi::um::winuser::{
    SetWindowsHookExW,
    UnhookWindowsHookEx,
    GetMessageW,
    TranslateMessage,
    DispatchMessageW,
    WH_KEYBOARD_LL,
    MSG,
    WM_HOTKEY,
    RegisterHotKey,
    UnregisterHotKey,
    MOD_ALT,
    MOD_NOREPEAT,
    VK_MENU,
    WM_KEYUP,
};
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
        unsafe {
            // 创建并初始化键盘管理器
            let mut keyboard_manager = keyboard::KeyboardManager::new();
            keyboard_manager.set_indicator(&mut self.indicator);
            KEYBOARD_MANAGER = Some(keyboard_manager);

            // 设置键盘钩子
            self.keyboard_hook = SetWindowsHookExW(
                WH_KEYBOARD_LL,
                Some(keyboard::keyboard_hook_proc),
                std::ptr::null_mut(),
                0,
            );

            if self.keyboard_hook.is_null() {
                anyhow::bail!("无法设置键盘钩子");
            }

            // 注册热键，使用 MOD_NOREPEAT 防止重复触发
            if RegisterHotKey(null_mut(), 1, MOD_ALT as u32 | MOD_NOREPEAT as u32, b'H' as u32) == 0 {
                log::warn!("注册 Alt+H 热键失败: {}", std::io::Error::last_os_error());
            } else {
                log::debug!("成功注册 Alt+H 热键");
            }
            
            if RegisterHotKey(null_mut(), 2, MOD_ALT as u32 | MOD_NOREPEAT as u32, b'L' as u32) == 0 {
                log::warn!("注册 Alt+L 热键失败: {}", std::io::Error::last_os_error());
            } else {
                log::debug!("成功注册 Alt+L 热键");
            }
        }

        Ok(())
    }

    fn message_loop(&mut self) -> anyhow::Result<()> {
        let mut msg: MSG = unsafe { std::mem::zeroed() };
        let mut alt_was_pressed = false;  // 添加这个变量来跟踪 Alt 键状态
        
        unsafe {
            while GetMessageW(&mut msg, null_mut(), 0, 0) > 0 {
                match msg.message {
                    WM_HOTKEY => {
                        log::debug!("收到热键消息: wparam={}", msg.wParam);
                        if let Some(manager) = &mut KEYBOARD_MANAGER {
                            if let Some(window_manager) = manager.get_window_manager() {
                                match msg.wParam as i32 {
                                    1 => {
                                        log::debug!("处理 Alt+H 热键");
                                        window_manager.select_window(Direction::Left);
                                        alt_was_pressed = true;
                                    },
                                    2 => {
                                        log::debug!("处理 Alt+L 热键");
                                        window_manager.select_window(Direction::Right);
                                        alt_was_pressed = true;
                                    },
                                    _ => {}
                                }
                            }
                        }
                    },
                    WM_KEYUP => {
                        // 检查是否是 Alt 键释放
                        if msg.wParam == VK_MENU as usize && alt_was_pressed {
                            if let Some(manager) = &mut KEYBOARD_MANAGER {
                                if let Some(window_manager) = manager.get_window_manager() {
                                    window_manager.finish_switching();
                                    alt_was_pressed = false;
                                }
                            }
                        }
                    },
                    _ => {
                        TranslateMessage(&msg);
                        DispatchMessageW(&msg);
                    }
                }
            }
        }

        Ok(())
    }

    // 添加清理方法
    fn cleanup(&mut self) {
        unsafe {
            // 注销热键
            UnregisterHotKey(null_mut(), 1);
            UnregisterHotKey(null_mut(), 2);

            // 清理钩子
            if !self.keyboard_hook.is_null() {
                UnhookWindowsHookEx(self.keyboard_hook);
                self.keyboard_hook = null_mut();
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
