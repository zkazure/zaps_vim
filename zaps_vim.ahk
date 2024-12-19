#SingleInstance Force


#Include lib ; official function path




global press_caps

CapsLock::
{
    global press_caps
    press_caps:=1
    CapsLock:=""

    KeyWait("CapsLock")
    press_caps:=0
    return
}


#CapsLock::
{
    MsgBox("1")
}
^CapsLock::
{
    MsgBox("2")
}

; change chinese and english
!CapsLock::
{
    ;MsgBox("3")
    Send ("^ ")
}
+CapsLock::
{
    MsgBox("4")
}

; basic vim-like
#HotIf (GetKeyState("CapsLock", "P"))
k::Send("{Up 1}")
j::Send("{Down 1}")
h::Send("{Left 1}")
l::Send("{Right 1}")
[::Send("{Esc}")
Space::Send("{Enter}")
F5:: Reload
i::Send("{BackSpace}")
o::Send("{Delete}")
/*
global ctrlZ, CapsLock2, CapsLock

CapsLock::{
    ; 以下是对各变量含义的注释
    ; ctrlZ:     Capslock+Z undo / redo flag
    ; Capslock:  Capslock 键状态标记，按下是1，松开是0
    ; Capslock2: 是否使用过 Capslock+ 功能标记，使用过会清除这个变量
    ;ctrlZ := CapsLock2 := CapsLock := 1

    ;SetTimer("setCapsLock2", -100) ; 300ms 犹豫操作时间，在v2中SetTimer参数传递方式改变，函数名要用双引号括起来作为字符串传入

    ;SetTimer("changeMouseSpeed", 50) ; 暂时修改鼠标速度，同样按v2语法修改SetTimer调用方式

    KeyWait("CapsLock") ; 在v2中KeyWait函数参数要用双引号括起来，这里等待CapsLock键被按下或者松开（取决于后续代码逻辑）
    CapsLock := "" ; Capslock最优先置空，来关闭 Capslock+ 功能的触发
    if (CapsLock2) {
        if (keyset.press_caps) {
            try {
                runFunc(keyset.press_caps)
            } catch {
            }
        } else {
            SetCapsLockState((GetKeyState("CapsLock", "T")? "Off" : "On"))
        }
        ; SendInput "{esc}" ; 在v2中SendInput发送按键也有语法规范，这里注释掉原有的，若要启用需按正确格式写
    }
    CapsLock2 := ""
}
*/

; Base command



/*
*CapsLock::{
    SetCapsLockState("AlwaysOff") 
}


^CapsLock::{
    SetCapsLockState("On") 
}
*/
/*
CapsLock & Tab::{
    if (GetKeyState("CapsLock", "T")) {
        SetCapsLockState("Off")
    } else {
        SetCapsLockState("On")
    }
    return
}
*/
; Now CapsLock is lose effectiveness, but you could still enable toggle it with modifier keys and CapsLock
/*
CapsLock::{

    KeyWait("CapsLock", "D")
    if (A_TimeSinceThisHotkey < 500) {
        KeyWait("CapsLock", "U")
        if (A_TimeSinceThisHotkey < 500) {
            SetCapsLockState("Toggle")
        }
    }
    return
}
*/

; Change Chinese and English
/*
CapsLock & Tab::
{   
    CapsLock:=""
    Send ("^ ")
}
*/