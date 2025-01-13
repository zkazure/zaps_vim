use winapi::shared::windef::{HWND, HBRUSH, HFONT, RECT, COLORREF};
use winapi::um::winuser::{
    GetForegroundWindow,
    SetForegroundWindow,
    IsWindowVisible,
    GetWindowTextW,
    EnumWindows,
    CreateWindowExW,
    ShowWindow,
    SetWindowPos,
    GetSystemMetrics,
    WNDCLASSEXW,
    RegisterClassExW,
    WS_POPUP,
    WS_EX_TOPMOST,
    WS_EX_LAYERED,
    WS_EX_TOOLWINDOW,
    SW_SHOW,
    SW_HIDE,
    SM_CXSCREEN,
    SM_CYSCREEN,
    HWND_TOPMOST,
    CreateFontW,
    GetDC,
    ReleaseDC,
    FillRect,
    DrawTextW,
    BeginPaint,
    EndPaint,
    PAINTSTRUCT,
    WM_PAINT,
    DT_CENTER,
    DT_VCENTER,
    DT_SINGLELINE,
    COLOR_WINDOW,
};
use winapi::um::wingdi::{
    CreateSolidBrush,
    DeleteObject,
    SetBkMode,
    SetTextColor,
    TRANSPARENT,
};
use std::ptr::null_mut;
use std::collections::VecDeque;

/// 窗口切换的方向枚举
/// 支持上下左右四个方向的切换
#[derive(Debug, PartialEq, Clone)]
pub enum Direction {
    Left,   // 向左切换窗口
    Right,  // 向右切换窗口
    Up,     // 向上切换窗口
    Down,   // 向下切换窗口
}

/// 窗口管理器结构体
/// 负责管理所有窗口的切换和显示
pub struct WindowManager {
    current_window: HWND,          // 当前激活的窗口句柄
    window_list: VecDeque<HWND>,   // 所有可切换窗口的列表
    selected_index: usize,         // 当前选中的窗口索引
    switcher_window: HWND,         // 窗口切换器的窗口句柄
    switching: bool,               // 是否正在切换窗口的标志
}

impl WindowManager {
    /// 创建一个新的窗口管理器实例
    pub fn new() -> Self {
        Self {
            current_window: null_mut(),    // 初始化为空指针
            window_list: VecDeque::new(),  // 创建空的窗口列表
            selected_index: 0,             // 初始选中索引为0
            switcher_window: null_mut(),   // 切换器窗口初始化为空
            switching: false,              // 初始状态不在切换中
        }
    }

    /// 开始窗口切换模式
    /// 当用户按下 Alt 键时调用此方法
    pub fn start_switching(&mut self) {
        if !self.switching {
            self.switching = true;
            // 更新可切换的窗口列表
            self.update_window_list();
            unsafe {
                // 如果切换器窗口还没创建，创建它
                if self.switcher_window.is_null() {
                    self.create_switcher_window();
                }
                // 显示切换器窗口
                ShowWindow(self.switcher_window, SW_SHOW);
                // 更新显示内容
                self.update_switcher_display();
            }
        }
    }

    /// 选择窗口
    /// 当用户按下 H/J/K/L 键时调用此方法来切换选中的窗口
    pub fn select_window(&mut self, direction: Direction) {
        if !self.switching || self.window_list.is_empty() {
            return;
        }

        // 根据方向更新选中的窗口索引
        match direction {
            Direction::Left | Direction::Up => {
                // 向左或向上切换，索引减1
                if self.selected_index > 0 {
                    self.selected_index -= 1;
                } else {
                    // 如果已经是第一个，循环到最后一个
                    self.selected_index = self.window_list.len() - 1;
                }
            },
            Direction::Right | Direction::Down => {
                // 向右或向下切换，索引加1
                self.selected_index = (self.selected_index + 1) % self.window_list.len();
            }
        }

        // 更新切换器窗口的显示
        self.update_switcher_display();
    }

    /// 结束窗口切换
    /// 当用户松开 Alt 键时调用此方法
    pub fn finish_switching(&mut self) {
        if self.switching {
            self.switching = false;
            unsafe {
                // 隐藏切换器窗口
                ShowWindow(self.switcher_window, SW_HIDE);
                // 激活选中的窗口
                if let Some(&hwnd) = self.window_list.get(self.selected_index) {
                    SetForegroundWindow(hwnd);
                    ShowWindow(hwnd, SW_SHOW);
                }
            }
        }
    }

    /// 更新可切换窗口的列表
    /// 使用 Windows API 枚举所有可见窗口
    fn update_window_list(&mut self) {
        // 清空现有的窗口列表
        self.window_list.clear();
        
        unsafe {
            // EnumWindows 是 Windows API 提供的函数，用于枚举所有顶层窗口
            // 第一个参数是回调函数，第二个参数是传递给回调函数的数据
            // 这里我们传递窗口列表的指针，以便在回调中添加窗口
            EnumWindows(Some(Self::enum_window_proc), &mut self.window_list as *mut _ as isize);
        }
    }

    /// Windows API 回调函数，用于处理每个枚举到的窗口
    /// - hwnd: 窗口句柄
    /// - l_param: 传入的参数（这里是窗口列表的指针）
    /// 返回1表示继续枚举，返回0表示停止枚举
    unsafe extern "system" fn enum_window_proc(hwnd: HWND, l_param: isize) -> i32 {
        // 将传入的参数转换回窗口列表的可变引用
        let window_list = &mut *(l_param as *mut VecDeque<HWND>);
        
        // 检查窗口是否有效，如果有效则添加到列表中
        if WindowManager::is_valid_window(hwnd) {
            window_list.push_back(hwnd);
        }
        
        1  // 返回1继续枚举下一个窗口
    }

    /// 检查窗口是否是有效的可切换窗口
    /// - hwnd: 要检查的窗口句柄
    /// 返回 true 表示窗口可以被切换，false 表示窗口应该被忽略
    unsafe fn is_valid_window(hwnd: HWND) -> bool {
        // 首先检查窗口是否可见
        if IsWindowVisible(hwnd) == 0 {
            return false;
        }

        // 获取窗口标题
        let mut title = [0u16; 512];  // 创建缓冲区存储标题
        let len = GetWindowTextW(hwnd, title.as_mut_ptr(), title.len() as i32);
        
        // 检查窗口是否有标题（长度大于0）
        if len > 0 {
            // TODO: 可以在这里添加更多的过滤条件
            // 例如：排除任务栏、系统托盘等特殊窗口
            true
        } else {
            false
        }
    }

    /// 打印窗口信息到日志（用于调试）
    unsafe fn debug_window_info(&self, hwnd: HWND) {
        let mut title = [0u16; 512];
        let len = GetWindowTextW(hwnd, title.as_mut_ptr(), title.len() as i32);
        
        if len > 0 {
            // 将 UTF-16 编码的标题转换为 Rust 字符串
            let title = String::from_utf16_lossy(&title[..len as usize]);
            log::debug!("切换到窗口: {}", title);
        }
    }

    /// 创建窗口切换器的界面窗口
    unsafe fn create_switcher_window(&mut self) {
        // 创建窗口类名（必须以null结尾）
        let class_name: Vec<u16> = "PixelVimSwitcher\0".encode_utf16().collect();
        
        // 配置窗口类
        let wc = WNDCLASSEXW {
            cbSize: std::mem::size_of::<WNDCLASSEXW>() as u32,  // 结构体大小
            style: CS_HREDRAW | CS_VREDRAW,  // 窗口样式：当大小改变时重绘
            lpfnWndProc: Some(Self::switcher_window_proc),  // 窗口消息处理函数
            cbClsExtra: 0,  // 额外类内存
            cbWndExtra: 0,  // 额外窗口内存
            hInstance: null_mut(),  // 实例句柄
            hIcon: null_mut(),  // 图标
            hCursor: null_mut(),  // 鼠标指针
            hbrBackground: (COLOR_WINDOW + 1) as HBRUSH,  // 背景画刷
            lpszMenuName: null_mut(),  // 菜单名
            lpszClassName: class_name.as_ptr(),  // 类名
            hIconSm: null_mut(),  // 小图标
        };

        // 注册窗口类
        RegisterClassExW(&wc);

        // 创建切换器窗口
        self.switcher_window = CreateWindowExW(
            // 扩展样式：总在最前、支持透明、无任务栏图标
            WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
            class_name.as_ptr(),  // 类名
            "Window Switcher\0".encode_utf16().collect::<Vec<u16>>().as_ptr(),  // 窗口标题
            WS_POPUP,  // 弹出窗口样式
            0, 0, 800, 400,  // 初始位置和大小
            null_mut(),  // 父窗口
            null_mut(),  // 菜单
            null_mut(),  // 实例句柄
            null_mut(),  // 额外参数
        );

        // 将窗口移动到屏幕中央
        self.center_switcher_window();
    }

    /// 将切换器窗口居中显示
    unsafe fn center_switcher_window(&self) {
        // 获取屏幕尺寸
        let screen_width = GetSystemMetrics(SM_CXSCREEN);
        let screen_height = GetSystemMetrics(SM_CYSCREEN);
        let window_width = 800;
        let window_height = 400;

        // 计算居中位置
        let x = (screen_width - window_width) / 2;
        let y = (screen_height - window_height) / 2;

        // 设置窗口位置
        SetWindowPos(
            self.switcher_window,
            HWND_TOPMOST,  // 保持在最顶层
            x, y,  // 新的位置
            window_width, window_height,  // 窗口大小
            SWP_SHOWWINDOW,  // 显示窗口
        );
    }

    /// 更新切换器窗口的显示内容
    unsafe fn update_switcher_display(&self) {
        if self.switcher_window.is_null() {
            return;
        }

        // 使窗口重绘
        InvalidateRect(self.switcher_window, null_mut(), 1);
        UpdateWindow(self.switcher_window);
    }

    /// 切换器窗口的消息处理函数
    unsafe extern "system" fn switcher_window_proc(
        hwnd: HWND,
        msg: u32,
        w_param: WPARAM,
        l_param: LPARAM,
    ) -> LRESULT {
        match msg {
            // 处理窗口绘制消息
            WM_PAINT => {
                let mut ps: PAINTSTRUCT = std::mem::zeroed();
                let hdc = BeginPaint(hwnd, &mut ps);  // 开始绘制

                // 设置透明背景
                SetBkMode(hdc, TRANSPARENT as i32);

                // 创建用于显示文本的字体
                let font = CreateFontW(
                    24, 0, 0, 0,  // 高度24像素
                    400, 0, 0, 0,  // 正常粗细
                    0, 0, 0, 0, 0,
                    "Segoe UI\0".encode_utf16().collect::<Vec<u16>>().as_ptr(),
                );

                // 绘制所有窗口的标题
                if let Some(window_manager) = Self::get_window_manager(hwnd) {
                    let mut y_offset = 10;  // 第一个标题的垂直位置
                    
                    // 遍历所有窗口
                    for (i, &window) in window_manager.window_list.iter().enumerate() {
                        let mut title = [0u16; 512];
                        let len = GetWindowTextW(window, title.as_mut_ptr(), title.len() as i32);
                        
                        if len > 0 {
                            // 设置文本绘制区域
                            let mut rect = RECT {
                                left: 10,
                                top: y_offset,
                                right: 790,
                                bottom: y_offset + 30,
                            };

                            // 如果是当前选中的窗口，使用高亮显示
                            if i == window_manager.selected_index {
                                let brush = CreateSolidBrush(0x00A0A0A0);  // 灰色背景
                                FillRect(hdc, &rect, brush);
                                DeleteObject(brush as _);
                                SetTextColor(hdc, 0x00FFFFFF);  // 白色文字
                            } else {
                                SetTextColor(hdc, 0x00000000);  // 黑色文字
                            }

                            // 绘制窗口标题
                            DrawTextW(
                                hdc,
                                title.as_ptr(),
                                len,
                                &mut rect,
                                DT_SINGLELINE | DT_VCENTER,  // 单行，垂直居中
                            );

                            y_offset += 35;  // 下一个标题的位置
                        }
                    }
                }

                // 清理资源
                DeleteObject(font as _);
                EndPaint(hwnd, &ps);  // 结束绘制
                0
            }
            // 其他消息使用默认处理
            _ => DefWindowProcW(hwnd, msg, w_param, l_param),
        }
    }
} 