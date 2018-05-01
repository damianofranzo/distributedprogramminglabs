#include <stdio.h> //printf
#include <stdlib.h> //atoi
#include <signal.h>

#include "sockwrap.h" //Socket, Bind, Select etc etc
#include "errlib.h"

#define BUFFSIZE 50

void unlock(int signum);
volatile int flag=1;

char* prog_name;

int main(int argc,char** argv){
    if(argc!=2){
        printf("Usage:program port");
        return -1;
    }
    int sock=Socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    printf("Socket created\n");

    struct sockaddr_in saddr;

    char *buffer=malloc(BUFFSIZE);
    int nrbyte;

    socklen_t saddrlen;

    signal(SIGINT,unlock);

    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=htonl(INADDR_ANY);
    saddr.sin_port=htons(atoi(argv[1]));

    Bind(sock,(struct sockaddr*) &saddr,sizeof(saddr));
    printf("Bind executed with success\n");

    while(flag){
        //handle udp service
        nrbyte=(int)Recvfrom(sock,buffer,BUFFSIZE,0,(struct sockaddr*) &saddr,&saddrlen);
        fprintf(stdout,"message %s sent\n",buffer);
        Sendto(sock,buffer,nrbyte,0,(struct sockaddr*) &saddr, sizeof(saddr));
        //printf("what the hell is going on?!?\n\n%s",buffer);

    }

    printf("exit from the loop safely\n");
    free(buffer);
    Close(sock);

    return 1;
}

void unlock(int signum){
    flag=0;
}
