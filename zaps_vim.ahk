#SingleInstance Force

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
CapsLock::
{
    KeyWait("CapsLock", "D") ; D - Down  U - Up
    if (A_TimeSinceThisHotkey < 500) {
        KeyWait("CapsLock", "U")
        if (A_TimeSinceThisHotkey < 500) {
            SetCapsLockState("Toggle")
        }
    }
    return
}

