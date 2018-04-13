
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "sockwrap.h"

#include <string.h>

//it has to be declared outside, to be linked with the *proo_name var of sockwrap.c
char *prog_name;

int main(int argc, char** argv){
    int sock=Socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    uint32_t address;
    char addr_s[33];

    uint16_t port;
    int port_int;

    struct sockaddr_in addr_in;


    printf("Inserire ip del client e porta: \n");
    scanf("%s %d",addr_s,&port_int);


    //addr_in.sin_addr.s_addr=address;
    addr_in.sin_family=AF_INET;
    addr_in.sin_port=htons(port_int);
    inet_aton(addr_s,&addr_in.sin_addr);

    Connect(sock,(struct sockaddr*)&addr_in,sizeof(addr_in));

    printf("Connessione effettuata con successo\n");

    Close(sock);

    return 0;
}



