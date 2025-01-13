use winapi::shared::windef::{HWND, HBRUSH};
use winapi::shared::minwindef::{LPARAM, LRESULT, WPARAM};
use winapi::um::winuser::{
    CreateWindowExW, 
    RegisterClassExW,
    DefWindowProcW,
    ShowWindow,
    UpdateWindow,
    SetWindowPos,
    GetSystemMetrics,
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
use std::ptr::null_mut;
use crate::mode::Mode;

/// 状态指示器窗口的尺寸常量
const WINDOW_WIDTH: i32 = 100;   // 窗口宽度
const WINDOW_HEIGHT: i32 = 30;   // 窗口高度

/// 状态指示器结构体
/// 用于显示当前的工作模式和其他状态信息
pub struct StatusIndicator {
    window: HWND,           // 指示器窗口的句柄
    current_mode: Mode,     // 当前显示的模式
}

impl StatusIndicator {
    /// 创建新的状态指示器实例
    pub fn new() -> Self {
        Self {
            window: null_mut(),           // 窗口句柄初始化为空
            current_mode: Mode::Desktop,  // 默认显示桌面模式
        }
    }

    /// 显示状态指示器窗口
    pub fn show(&mut self) {
        unsafe {
            // 创建窗口（如果还没创建）
            self.create_window();
            if !self.window.is_null() {
                // 显示窗口并更新窗口内容
                ShowWindow(self.window, SW_SHOW);
                UpdateWindow(self.window);
                self.update_position();
            }
        }
    }

    /// 更新显示的模式
    /// 当模式发生变化时调用此方法
    pub fn update_mode(&mut self, mode: &Mode) {
        self.current_mode = mode.clone();
        unsafe {
            if !self.window.is_null() {
                // 强制窗口重绘以显示新的模式
                UpdateWindow(self.window);
            }
        }
        log::debug!("更新模式显示: {:?}", mode);
    }

    /// 创建指示器窗口
    /// 这是一个内部方法，只在需要时调用
    unsafe fn create_window(&mut self) {
        // 注册窗口类
        let class_name: Vec<u16> = "PixelVimIndicator\0".encode_utf16().collect();
        let wc = WNDCLASSEXW {
            cbSize: std::mem::size_of::<WNDCLASSEXW>() as u32,
            style: CS_HREDRAW | CS_VREDRAW,
            lpfnWndProc: Some(Self::window_proc),
            cbClsExtra: 0,
            cbWndExtra: 0,
            hInstance: null_mut(),
            hIcon: null_mut(),
            hCursor: null_mut(),
            hbrBackground: 16 as HBRUSH,  // COLOR_WINDOW + 1
            lpszMenuName: null_mut(),
            lpszClassName: class_name.as_ptr(),
            hIconSm: null_mut(),
        };

        RegisterClassExW(&wc);

        // 创建窗口
        self.window = CreateWindowExW(
            WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
            class_name.as_ptr(),
            "Mode\0".encode_utf16().collect::<Vec<u16>>().as_ptr(),
            WS_POPUP,
            0, 0,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            null_mut(),
            null_mut(),
            null_mut(),
            null_mut(),
        );
    }

    /// 更新窗口位置
    /// 将窗口移动到屏幕右下角
    unsafe fn update_position(&self) {
        if self.window.is_null() {
            return;
        }

        // 获取屏幕尺寸
        let screen_width = GetSystemMetrics(SM_CXSCREEN);
        let screen_height = GetSystemMetrics(SM_CYSCREEN);

        // 计算窗口位置（右下角）
        let x = screen_width - WINDOW_WIDTH - 20;
        let y = screen_height - WINDOW_HEIGHT - 20;

        // 设置窗口位置
        SetWindowPos(
            self.window,
            HWND_TOPMOST,
            x,
            y,
            0,
            0,
            SWP_NOSIZE | SWP_SHOWWINDOW,
        );
    }

    /// 窗口消息处理函数
    unsafe extern "system" fn window_proc(
        hwnd: HWND,
        msg: u32,
        w_param: WPARAM,
        l_param: LPARAM,
    ) -> LRESULT {
        // 使用默认的窗口处理过程
        DefWindowProcW(hwnd, msg, w_param, l_param)
    }
}

/// 实现 Drop trait 以确保资源被正确清理
impl Drop for StatusIndicator {
    fn drop(&mut self) {
        unsafe {
            // 如果窗口存在，销毁它
            if !self.window.is_null() {
                winapi::um::winuser::DestroyWindow(self.window);
            }
        }
    }
} 