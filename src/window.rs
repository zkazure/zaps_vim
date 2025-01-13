use winapi::shared::windef::HWND;
use winapi::um::winuser::{
    GetForegroundWindow,
    SetForegroundWindow,
    IsWindowVisible,
    GetWindowTextW,
    ShowWindow,
    BringWindowToTop,
    SW_RESTORE,
    SW_HIDE,
    EnumWindows,
    CreateWindowExW,
    RegisterClassW,
    DefWindowProcW,
    SetWindowPos,
    GetSystemMetrics,
    WNDCLASSW,
    CS_HREDRAW,
    CS_VREDRAW,
    WS_POPUP,
    WS_EX_TOOLWINDOW,
    WS_EX_LAYERED,
    HWND_TOPMOST,
    SM_CXSCREEN,
    SM_CYSCREEN,
    SWP_SHOWWINDOW,
    DestroyWindow,
};
use std::ptr::null_mut;

/// 窗口切换方向枚举
#[derive(Debug, PartialEq)]
pub enum Direction {
    Left,   // 向左切换
    Right,  // 向右切换
    Up,     // 向上切换
    Down,   // 向下切换
}

/// 窗口管理器结构体
pub struct WindowManager {
    current_window: HWND,
    window_list: Vec<HWND>,
    switcher_window: HWND,
    current_index: usize,  // 添加当前索引记录
    is_switching: bool,    // 添加切换状态标记
}

impl WindowManager {
    /// 创建新的窗口管理器实例
    pub fn new() -> Self {
        Self {
            current_window: null_mut(),
            window_list: Vec::new(),
            switcher_window: null_mut(),
            current_index: 0,
            is_switching: false,
        }
    }

    /// 选择窗口
    pub fn select_window(&mut self, direction: Direction) {
        unsafe {
            // 只在开始切换时更新窗口列表
            if !self.is_switching {
                self.update_window_list();
                self.is_switching = true;
                self.current_index = self.window_list.iter()
                    .position(|&w| w == GetForegroundWindow())
                    .unwrap_or(0);
            }
            
            if self.window_list.len() <= 1 {
                log::debug!("没有其他可切换的窗口");
                return;
            }

            // 计算下一个窗口的索引
            self.current_index = match direction {
                Direction::Left => {
                    if self.current_index == 0 {
                        self.window_list.len() - 1
                    } else {
                        self.current_index - 1
                    }
                },
                Direction::Right => {
                    if self.current_index == self.window_list.len() - 1 {
                        0
                    } else {
                        self.current_index + 1
                    }
                },
                _ => self.current_index,
            };

            log::debug!("切换到窗口索引: {}", self.current_index);

            // 显示预览窗口
            self.show_switcher(self.current_index);

            // 切换到选中的窗口
            if let Some(&next_window) = self.window_list.get(self.current_index) {
                log::debug!("切换到窗口: {:?}", next_window);
                // 先恢复最小化的窗口
                ShowWindow(next_window, SW_RESTORE);
                // 然后设置为前台窗口
                SetForegroundWindow(next_window);
            }
        }
    }

    /// 更新窗口列表
    unsafe fn update_window_list(&mut self) {
        self.window_list.clear();
        
        unsafe extern "system" fn enum_window_proc(hwnd: HWND, l_param: isize) -> i32 {
            let window_list = &mut *(l_param as *mut Vec<HWND>);
            
            if IsWindowVisible(hwnd) != 0 {
                let mut title: [u16; 512] = [0; 512];
                let title_len = GetWindowTextW(hwnd, title.as_mut_ptr(), 512) as usize;
                
                if title_len > 0 {
                    window_list.push(hwnd);
                }
            }
            1
        }

        EnumWindows(
            Some(enum_window_proc),
            &mut self.window_list as *mut Vec<HWND> as isize,
        );

        self.current_window = GetForegroundWindow();
        
        if !self.window_list.contains(&self.current_window) && !self.current_window.is_null() {
            self.window_list.insert(0, self.current_window);
        }
    }

    /// 显示切换预览窗口
    unsafe fn show_switcher(&mut self, selected_index: usize) {
        // 如果预览窗口不存在，创建它
        if self.switcher_window.is_null() {
            self.create_switcher_window();
        }

        // 获取屏幕尺寸
        let screen_width = GetSystemMetrics(SM_CXSCREEN);
        let screen_height = GetSystemMetrics(SM_CYSCREEN);

        // 设置窗口位置（屏幕中央）
        let window_width = 400;
        let window_height = 300;
        let x = (screen_width - window_width) / 2;
        let y = (screen_height - window_height) / 2;

        SetWindowPos(
            self.switcher_window,
            HWND_TOPMOST,
            x, y,
            window_width,
            window_height,
            SWP_SHOWWINDOW,
        );
    }

    /// 创建切换预览窗口
    unsafe fn create_switcher_window(&mut self) {
        let class_name = "WindowSwitcher\0".encode_utf16().collect::<Vec<u16>>();
        let window_name = "Window Switcher\0".encode_utf16().collect::<Vec<u16>>();

        let wc = WNDCLASSW {
            style: CS_HREDRAW | CS_VREDRAW,
            lpfnWndProc: Some(DefWindowProcW),
            cbClsExtra: 0,
            cbWndExtra: 0,
            hInstance: null_mut(),
            hIcon: null_mut(),
            hCursor: null_mut(),
            hbrBackground: null_mut(),
            lpszMenuName: null_mut(),
            lpszClassName: class_name.as_ptr(),
        };

        RegisterClassW(&wc);

        self.switcher_window = CreateWindowExW(
            WS_EX_TOOLWINDOW | WS_EX_LAYERED,
            class_name.as_ptr(),
            window_name.as_ptr(),
            WS_POPUP,
            0, 0, 0, 0,
            null_mut(),
            null_mut(),
            null_mut(),
            null_mut(),
        );
    }

    /// 开始切换
    pub fn start_switching(&mut self) {
        self.is_switching = true;
        unsafe {
            self.update_window_list();
            self.current_index = self.window_list.iter()
                .position(|&w| w == GetForegroundWindow())
                .unwrap_or(0);
        }
    }

    /// 结束切换
    pub fn finish_switching(&mut self) {
        unsafe {
            if !self.switcher_window.is_null() {
                // 隐藏切换窗口
                ShowWindow(self.switcher_window, SW_HIDE);
                // 销毁窗口
                DestroyWindow(self.switcher_window);
                self.switcher_window = null_mut();
            }
        }
        self.is_switching = false;
    }
} 