; This code in order to make CapsLock in vain, but we could still record the status of the key.

/* This is an example
global flag

CapsLock::
{
    CapsLock:=""
    flag:=1
    MsgBox(flag)
    KeyWait("CapsLock")
    flag:=0
    MsgBox(flag)
}
*/

press(flag)
{
    flag:=""
}
