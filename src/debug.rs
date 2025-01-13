use winapi::um::winuser::{MOD_ALT, MOD_SHIFT};
use winapi::shared::minwindef::DWORD;

// 添加调试辅助函数
pub fn debug_key_event(vk_code: DWORD, flags: DWORD) {
    log::debug!(
        "按键事件: vk_code={}, flags={:b}, mod_alt={}, mod_shift={}", 
        vk_code,
        flags,
        flags & MOD_ALT as DWORD != 0,
        flags & MOD_SHIFT as DWORD != 0
    );
}

// 键盘管理器的调试扩展
use crate::keyboard::KeyboardManager;

impl KeyboardManager {
    pub fn debug_handle_key(&mut self, vk_code: DWORD, flags: DWORD) -> bool {
        debug_key_event(vk_code, flags);
        self.handle_key(vk_code, flags)
    }
} 