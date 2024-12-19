This repo in order to create a script to enable me to use vim-like control on Windows with autohotkey v2.

## Goal Function

- [ ] move with hjkl.
- [ ] escape with ctrl + leftSquareBracket.
- [ ] enter without move hands.

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