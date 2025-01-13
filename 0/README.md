This repo in order to create a script to enable me to use vim-like control on Windows with autohotkey v2.

## Goal Function
- [ ] This software should be the easy win-vind, I could not use the  win-vind. 我觉得现在的win-vind还不好用。

- [x] move with hjkl.
- [x] escape with ctrl + leftSquareBracket.
- [x] enter without move hands.
- [x] Switch between Chinese and English with alt + CapsLock
- [ ] delete the backquote function, if fn is easy to press
- [ ] if fn is easy to press, then the f1-f9 should be use.
- [ ] maybe i should change the menu and the rctrl.
- [ ] 增加一个切换窗口、切换桌面的命令
//
- [ ] Toggle case.
//
- [ ] Numeric Keypad Area in the right hand. use CapsLock shift lalt win, because you are able to press with your left hand.nm,mnm,dsjlksdv\\\dfadsaerqew
- [ ] make a myself everything.
- [ ] clipboard
- [ ] CapsLock+ to input english symbol.
- [ ] Some icons
- [ ] load animation
//
- [ ] learn more hotkeys
- [ ] 使用快捷键ctrl ralt wasd移动鼠标或者使用hjkl实现不同速度移动鼠标或者其他快捷键
- [ ] 到底应该替换什么快捷键，这需要看我的新键盘到了之后如何。
//
- [ ] suit to different application.
    - what application is used most frequenctly.
    - broswer use ctrl shift + number select from the other side 
    - should not create a new page every time.
- [ ] i need to add a hotkey in. to accept different command.
- [ ] 我应该写一个接口调用不同的配置文件，方便使用，最后或许还可以写一个GUI。
- [ ] should be able to control different windows with hotkey, close, change, drag, pin, transparent.
- [ ] add a utool similar to the mouse toolkit.
//
- [ ] what progamming language that vim writed with
- [ ] write a corresponding terminal editor. 
- [ ] 利用图形界面的方框大小判定方向键的移动
- [ ] 这么做下去可能不是autohotkey可以完成的事情了。一方面我需要搭建一个虚拟机，一方面我需要搭建另一个仓库保存我所有的开发日志，一方面我需要学习其他语言了。

## Learn autoHotkey

### Example

```AutoHotkey
a::
{
    SendInput, My first script
    return
}
```
### Annotation

```AutoHotkey
#SingleInstance Force

; This is a single line annotation 

/*
This is a multiline annotation
This is a multiline annotation
This is a multiline annotation
*/
```

### Basic Function

### Run

use Run and in the "", just operate as in the powershell(or windows terminal).

```AutoHotkey
Run "notepad <the path of file>"
```

- Remember do not contain space in the path

### Specific Symbol

```AutoHotkey

* ; This make sure no matter what key you press before, this hotkey still function well.
``` 

### Send

In this case, press a, and will toggle ctrl and Space
```AutoHotkey
a::
{
    Send ("^ ")
}
```
