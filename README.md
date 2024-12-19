This repo in order to create a script to enable me to use vim-like control on Windows with autohotkey v2.

## Goal Function

- [x] move with hjkl.
- [x] escape with ctrl + leftSquareBracket.
- [x] enter without move hands.
- [x] Switch between Chinese and English with alt + CapsLock
- [ ] delete the backquote function, if fn is easy to press
- [ ] if fn is easy to press, then the f1-f9 should be use.
- [ ] maybe i should change the menu and the rctrl.

- [ ] Toggle case.

- [ ] Numeric Keypad Area in the right hand. use CapsLock shift lalt win, because you are able to press with your left hand.nm,mnm,dsjlksdv\\\dfadsaerqew
- [ ] make a myself everything.
- [ ] clipboard
- [ ] CapsLock+ to input english symbol.
- [ ] Some icons
- [ ] load animation

- [ ] learn more hotkeys
- [ ] 使用快捷键ctrl ralt wasd移动鼠标或者使用hjkl实现不同速度移动鼠标或者其他快捷键
- [ ] 到底应该替换什么快捷键，这需要看我的新键盘到了之后如何。


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
