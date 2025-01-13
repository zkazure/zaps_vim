#[cfg(test)]
mod tests {
    use super::*;

    // 测试模式切换
    #[test]
    fn test_mode_toggle() {
        let mut mode_manager = ModeManager::new();
        
        // 确认初始模式是 Desktop
        assert_eq!(*mode_manager.current_mode(), Mode::Desktop);
        
        // 测试模式切换
        mode_manager.toggle_mode();
        assert_eq!(*mode_manager.current_mode(), Mode::Normal);
        
        // 再次切换回 Desktop 模式
        mode_manager.toggle_mode();
        assert_eq!(*mode_manager.current_mode(), Mode::Desktop);
    }

    // 测试按键处理
    #[test]
    fn test_key_handling() {
        let mut keyboard_manager = KeyboardManager::new();
        
        // 测试 Esc 键
        assert!(keyboard_manager.handle_key(VK_ESCAPE, 0));
        
        // 测试 Alt+H
        assert!(keyboard_manager.handle_key(VK_H, MOD_ALT));
    }
} 