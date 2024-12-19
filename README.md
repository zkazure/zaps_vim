This repo in order to create a script to enable me to use vim-like control on Windows with autohotkey v2.

## Goal Function

- [x] move with hjkl.
- [x] escape with ctrl + leftSquareBracket.
- [x] enter without move hands.
- [x] Switch between Chinese and English with alt + CapsLock

- [ ] Toggle case.
- [ ] add 系统托盘

- [ ] Numeric Keypad Area in the right hand
- [ ] make a myself everything.
- [ ] clipboard
- [ ] CapsLock+ to input english symbol.
- [ ] Some icons
- [ ] load animation

## Using Docs


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