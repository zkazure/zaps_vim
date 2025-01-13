use winapi::shared::minwindef::{WPARAM, LPARAM, LRESULT, DWORD};
use winapi::um::winuser::{
    CallNextHookEx, 
    KBDLLHOOKSTRUCT,
    VK_MENU,
    GetKeyState,
};
use std::ptr::null_mut;
use crate::window::Direction;
use crate::indicator;

/// 按键类型枚举
/// 用于表示不同的按键方向
#[derive(Debug)]
pub enum Key {
    Left,   // 左方向键
    Right,  // 右方向键
    Up,     // 上方向键
    Down,   // 下方向键
}

/// 键盘管理器结构体
/// 负责处理所有的键盘事件和按键逻辑
pub struct KeyboardManager {
    mode_manager: super::mode::ModeManager,      // 模式管理器
    window_manager: Option<super::window::WindowManager>, // 窗口管理器
    indicator: Option<*mut indicator::StatusIndicator>, // 状态指示器
    alt_pressed: bool,         // Alt 键是否被按下
    switching_windows: bool,   // 是否正在切换窗口
}

impl KeyboardManager {
    /// 创建新的键盘管理器实例
    pub fn new() -> Self {
        Self {
            mode_manager: super::mode::ModeManager::new(),
            window_manager: Some(super::window::WindowManager::new()),
            indicator: None,
            alt_pressed: false,
            switching_windows: false,
        }
    }

    /// 设置状态指示器
    /// 用于在模式切换时更新界面显示
    pub fn set_indicator(&mut self, indicator: &mut indicator::StatusIndicator) {
        self.indicator = Some(indicator as *mut _);
    }

    /// 处理键盘事件
    /// - vk_code: 虚拟键码
    /// - flags: 按键标志
    /// - event_type: 事件类型（按下、释放等）
    pub fn handle_key(&mut self, vk_code: DWORD, flags: DWORD) -> bool {
        // 检查是否是按键释放事件
        let is_key_up = (flags & 0x80000000) != 0;

        // 处理 Alt 键
        if vk_code == VK_MENU as u32 {
            if is_key_up {
                // Alt 键释放时结束切换
                if let Some(window_manager) = &mut self.window_manager {
                    window_manager.finish_switching();
                }
                self.alt_pressed = false;
            } else {
                // Alt 键按下时开始切换
                if let Some(window_manager) = &mut self.window_manager {
                    window_manager.start_switching();
                }
                self.alt_pressed = true;
            }
            return false;
        }

        // 如果 Alt 键被按下，让热键处理程序来处理 H 和 L 键
        let alt_state = unsafe { GetKeyState(VK_MENU as i32) };
        if (alt_state as u16 & 0x8000u16) != 0 {
            const VK_H: i32 = b'H' as i32;
            const VK_L: i32 = b'L' as i32;

            match vk_code as i32 {
                VK_H | VK_L => {
                    // 返回 false，让热键处理程序来处理
                    return false;
                }
                _ => {}
            }
        } else if self.alt_pressed {
            // Alt 键已经松开
            if let Some(window_manager) = &mut self.window_manager {
                window_manager.finish_switching();
            }
            self.alt_pressed = false;
        }

        false
    }

    /// 发送按键事件（预留接口）
    fn send_key(&mut self, key: Key) {
        log::debug!("发送按键: {:?}", key);
    }

    /// 获取窗口管理器的可变引用
    pub fn get_window_manager(&mut self) -> Option<&mut super::window::WindowManager> {
        self.window_manager.as_mut()
    }
}

/// 全局键盘管理器实例
/// 用于在钩子回调函数中访问键盘管理器
pub static mut KEYBOARD_MANAGER: Option<KeyboardManager> = None;

/// 全局键盘钩子回调函数
/// 处理所有的键盘事件
pub unsafe extern "system" fn keyboard_hook_proc(
    code: i32,
    w_param: WPARAM,
    l_param: LPARAM,
) -> LRESULT {
    // 如果 code < 0，必须调用下一个钩子
    if code < 0 {
        return CallNextHookEx(null_mut(), code, w_param, l_param);
    }

    // 获取按键信息
    let kb_struct = *(l_param as *const KBDLLHOOKSTRUCT);
    
    // 如果有键盘管理器，尝试处理按键
    if let Some(manager) = &mut KEYBOARD_MANAGER {
        if manager.handle_key(kb_struct.vkCode, kb_struct.flags) {
            return 1;  // 返回1表示我们处理了这个按键
        }
    }

    // 如果我们没有处理这个按键，传递给下一个钩子
    CallNextHookEx(null_mut(), code, w_param, l_param)
} 