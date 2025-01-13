use winapi::shared::windef::{HWND, HBRUSH, RECT};
use winapi::shared::minwindef::{WPARAM, LPARAM, LRESULT};
use winapi::um::winuser::{
    CreateWindowExW,
    RegisterClassExW,
    DefWindowProcW,
    ShowWindow,
    UpdateWindow,
    SetWindowPos,
    GetSystemMetrics,
    InvalidateRect,
    WNDCLASSEXW,
    WS_POPUP,
    WS_EX_TOPMOST,
    WS_EX_LAYERED,
    WS_EX_TOOLWINDOW,
    SW_SHOW,
    SM_CXSCREEN,
    SM_CYSCREEN,
    CS_HREDRAW,
    CS_VREDRAW,
    HWND_TOPMOST,
    SWP_NOSIZE,
    SWP_SHOWWINDOW,
};
use winapi::um::winuser::{
    CallNextHookEx, 
    KBDLLHOOKSTRUCT,
    WM_KEYDOWN,
    WM_KEYUP,
    WM_SYSKEYDOWN,
    WM_SYSKEYUP,
    VK_ESCAPE,
    VK_MENU,
};
use std::ptr::null_mut;
use crate::mode::Mode;
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
    window_manager: super::window::WindowManager, // 窗口管理器
    indicator: Option<*mut indicator::StatusIndicator>, // 状态指示器
    alt_pressed: bool,         // Alt 键是否被按下
    switching_windows: bool,   // 是否正在切换窗口
}

impl KeyboardManager {
    /// 创建新的键盘管理器实例
    pub fn new() -> Self {
        Self {
            mode_manager: super::mode::ModeManager::new(),
            window_manager: super::window::WindowManager::new(),
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
    pub fn handle_key(&mut self, vk_code: DWORD, flags: DWORD, event_type: u32) -> bool {
        match event_type {
            // 处理按键按下事件
            WM_KEYDOWN | WM_SYSKEYDOWN => {
                if vk_code == VK_MENU as DWORD {
                    self.alt_pressed = true;
                    self.window_manager.start_switching();
                    return true;
                }
                
                if self.alt_pressed {
                    self.handle_window_switch(vk_code)
                } else {
                    self.handle_desktop_key(vk_code, flags)
                }
            },
            // 处理按键释放事件
            WM_KEYUP | WM_SYSKEYUP => {
                if vk_code == VK_MENU as DWORD {
                    self.alt_pressed = false;
                    self.window_manager.finish_switching();
                    return true;
                }
                false
            },
            _ => false,
        }
    }

    /// 处理窗口切换快捷键
    /// 当按下 Alt+H/J/K/L 时调用
    fn handle_window_switch(&mut self, vk_code: DWORD) -> bool {
        // 定义虚拟键码常量
        const VK_H: DWORD = b'H' as DWORD;
        const VK_J: DWORD = b'J' as DWORD;
        const VK_K: DWORD = b'K' as DWORD;
        const VK_L: DWORD = b'L' as DWORD;

        match vk_code {
            code if code == VK_H => {
                self.window_manager.select_window(Direction::Left);
                true
            },
            code if code == VK_L => {
                self.window_manager.select_window(Direction::Right);
                true
            },
            code if code == VK_K => {
                self.window_manager.select_window(Direction::Up);
                true
            },
            code if code == VK_J => {
                self.window_manager.select_window(Direction::Down);
                true
            },
            _ => false,
        }
    }

    /// 处理普通模式下的按键
    /// 主要处理 Esc 和其他功能键
    fn handle_desktop_key(&mut self, vk_code: DWORD, flags: DWORD) -> bool {
        const VK_ESCAPE_U32: DWORD = VK_ESCAPE as DWORD;
        let _is_alt_pressed = flags & (1 << 29) != 0;  // 添加下划线前缀

        match vk_code {
            VK_ESCAPE_U32 => {
                // 切换模式并更新状态指示器
                self.mode_manager.toggle_mode();
                if let Some(indicator) = self.indicator {
                    unsafe {
                        (*indicator).update_mode(self.mode_manager.current_mode());
                    }
                }
                false
            },
            _ => false,
        }
    }

    /// 发送按键事件（预留接口）
    fn send_key(&mut self, key: Key) {
        log::debug!("发送按键: {:?}", key);
    }

    /// 获取窗口管理器的可变引用
    pub fn get_window_manager(&mut self) -> &mut super::window::WindowManager {
        &mut self.window_manager
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
        if manager.handle_key(kb_struct.vkCode, kb_struct.flags, w_param as u32) {
            return 1;  // 返回1表示我们处理了这个按键
        }
    }

    // 如果我们没有处理这个按键，传递给下一个钩子
    CallNextHookEx(null_mut(), code, w_param, l_param)
} 