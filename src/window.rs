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
    GetClassNameW,
    GetWindowLongW,
    GetWindowTextLengthW,
    GWL_STYLE,
    GWL_EXSTYLE,
    WS_CAPTION,
    WS_VISIBLE,
    GetWindowThreadProcessId,
    GetWindowInfo,
    WINDOWINFO,
    WS_OVERLAPPEDWINDOW,
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
            
            // 1. 检查窗口是否可见
            if IsWindowVisible(hwnd) == 0 {
                return 1;
            }

            // 2. 获取窗口标题
            let mut title: [u16; 512] = [0; 512];
            let title_len = GetWindowTextLengthW(hwnd);
            if title_len == 0 {
                return 1;
            }
            GetWindowTextW(hwnd, title.as_mut_ptr(), 512);
            let title_str = String::from_utf16_lossy(
                &title[..title.iter().position(|&x| x == 0).unwrap_or(512)]
            );

            // 3. 排除空标题或特定标题的窗口
            let excluded_titles = [
                "",
                "Program Manager",
                "Windows Input Experience",
                "Microsoft Text Input Application",
                "Windows Shell Experience Host",
            ];
            if excluded_titles.contains(&title_str.as_str()) {
                return 1;
            }

            // 4. 获取窗口类名
            let mut class_name: [u16; 512] = [0; 512];
            GetClassNameW(hwnd, class_name.as_mut_ptr(), 512);
            let class_str = String::from_utf16_lossy(
                &class_name[..class_name.iter().position(|&x| x == 0).unwrap_or(512)]
            );
            
            // 5. 排除特定的系统窗口类（移除了 ApplicationFrameWindow）
            let excluded_classes = [
                "Shell_TrayWnd",           // 任务栏
                "DV2ControlHost",          // 任务视图
                "Windows.UI.Core.CoreWindow", // UWP 核心窗口
                "Progman",                 // 程序管理器
                "WorkerW",                 // 桌面工作区
                "NotifyIconOverflowWindow", // 通知区域溢出窗口
                "WindowSwitcher",          // 我们自己的切换窗口
                "PopupMenu",               // 弹出菜单
                "tooltips_class32",        // 工具提示
                "ForegroundStaging",       // 前台暂存
                "WindowsDeferredUpdate",   // Windows 延迟更新
                "MultitaskingViewFrame",   // 多任务视图
                "Shell_SecondaryTrayWnd",  // 辅助任务栏
                "Windows.UI.Input.InputSite", // Windows 输入
                "MSCTFIME UI",            // 输入法界面
                "TrayNotifyWnd",          // 通知区域
                "Button",                 // 按钮
                "Static",                 // 静态控件
                "TaskListThumbnailWnd",   // 任务列表缩略图
                "PseudoConsoleWindow",    // 伪控制台窗口
                "TaskSwitcherWnd",        // 任务切换窗口
                "TaskSwitcherOverlay",    // 任务切换覆盖
            ];

            if excluded_classes.contains(&class_str.as_str()) {
                return 1;
            }

            // 6. 获取窗口样式
            let style = GetWindowLongW(hwnd, GWL_STYLE) as u32;
            let ex_style = GetWindowLongW(hwnd, GWL_EXSTYLE) as u32;
            
            // 7. 修改后的窗口样式检查逻辑
            // 放宽条件：只要是可见的主窗口即可
            if (style & (WS_VISIBLE | WS_CAPTION)) == 0 || 
               (ex_style & WS_EX_TOOLWINDOW) != 0 {
                // 特殊处理：如果是 UWP 应用或某些特定应用，即使不满足标准窗口样式也允许
                if class_str != "ApplicationFrameWindow" && 
                   !title_str.contains("微信") && 
                   !title_str.contains("企业微信") {
                    return 1;
                }
            }

            // 8. 检查窗口是否可用
            let mut info: WINDOWINFO = std::mem::zeroed();
            info.cbSize = std::mem::size_of::<WINDOWINFO>() as u32;
            if GetWindowInfo(hwnd, &mut info) == 0 {
                return 1;
            }

            // 9. 获取窗口所属进程
            let mut pid: u32 = 0;
            GetWindowThreadProcessId(hwnd, &mut pid);
            
            // 10. 如果进程 ID 为 0，说明是系统窗口
            if pid == 0 {
                return 1;
            }

            // 添加调试日志
            log::debug!("添加窗口: 标题='{}', 类名='{}'", title_str, class_str);

            // 所有检查都通过，添加到窗口列表
            window_list.push(hwnd);
            1
        }

        // 枚举所有顶级窗口
        EnumWindows(
            Some(enum_window_proc),
            &mut self.window_list as *mut Vec<HWND> as isize,
        );

        // 确保当前窗口在列表中（如果是有效窗口）
        let foreground = GetForegroundWindow();
        if !foreground.is_null() {
            let style = GetWindowLongW(foreground, GWL_STYLE) as u32;
            let ex_style = GetWindowLongW(foreground, GWL_EXSTYLE) as u32;
            
            // 只有当前窗口是有效的应用程序窗口时才添加
            if (style & WS_OVERLAPPEDWINDOW) != 0 && 
               (style & WS_CAPTION) != 0 && 
               (ex_style & WS_EX_TOOLWINDOW) == 0 &&
               !self.window_list.contains(&foreground) {
                self.window_list.insert(0, foreground);
            }
        }
    }

    /// 显示切换预览窗口
    unsafe fn show_switcher(&mut self, _selected_index: usize) {
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