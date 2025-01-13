# Pixel-vim

一个系统级的 vim 风格操作工具，让你能在整个 Windows 系统中使用 vim 快捷键。

## 特性

### 多模式支持
- 桌面模式 (Desktop Mode)：系统级导航和窗口管理
- 普通模式 (Normal Mode)：文本操作和导航
- 插入模式 (Insert Mode)：文本输入
- 可视模式 (Visual Mode)：文本选择
- 命令模式 (Command Mode)：执行命令

### 核心功能
1. 系统导航
   - 窗口切换和管理
   - 应用程序启动和切换
   - 无鼠标点击操作（类 Vimium `f` 键功能）

2. 文本编辑
   - vim 风格的文本操作
   - 多模式文本编辑
   - 复制粘贴增强

3. 可扩展性
   - 自定义模式接口
   - 快捷键配置
   - 插件系统

## 快捷键指南

### 系统操作
- `Alt + h/l` - 切换窗口
- `Alt + j/k` - 切换同一应用的窗口
- `s` - 显示点击提示
- `:q` - 关闭当前窗口
- `:w` - 保存
- `:wq` - 保存并关闭

### 文本导航
- `h/j/k/l` - 基本方向移动
- `w/b` - 词间移动
- `0/$` - 行首/行尾
- `gg/G` - 文档开始/结束
- `Ctrl+f/b` - 上下翻页
- `Ctrl+d/u` - 上下翻半页

### 文本编辑
- `i/a` - 进入插入模式
- `x` - 删除字符
- `dd` - 删除行
- `yy` - 复制行
- `p/P` - 粘贴
- `u` - 撤销
- `Ctrl+r` - 重做

### 搜索和跳转
- `f + 字符` - 向右查找字符
- `F + 字符` - 向左查找字符
- `/pattern` - 搜索
- `n/N` - 下一个/上一个匹配

## 安装和配置

1. 安装要求
   - Windows 系统
   - 管理员权限（用于全局快捷键）

2. 配置文件
   ```
   config/
   ├── keymap.json    # 快捷键配置
   ├── modes.json     # 模式配置
   └── settings.json  # 通用设置
   ```

## 开发说明

### 技术栈
- C++ 核心功能
- Windows API 系统交互
- UI Automation API 界面操作

### 构建方法 

```bash
bash

mkdir build

cd build

cmake ..

make
```

### 贡献指南

1. Fork 项目
2. 创建新分支
3. 提交修改
4. 创建 Pull Request

## 许可证
MIT License

## 致谢

- vim
- vimium
- win-vind

## 预计实现功能

- [ ] 中文输入法适配
- [ ] 插件系统
- [ ] 图形化实现快捷键配置