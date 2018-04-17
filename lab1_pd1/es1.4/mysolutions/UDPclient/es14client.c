/*
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

*/

/*
 *	struct in_addr { unsigned long s_addr; };
 *
 *	struct sockaddr_in {
 *		short            sin_family;   // e.g. AF_INET
 *		unsigned short   sin_port;     // e.g. htons(3490)
 *		struct in_addr   sin_addr;     // the previous one
 *		char             sin_zero[8];  // zero this if you want to
 *	};
 */



#include <sys/socket.h>
#include <sys/time.h> // timeval
#include <sys/select.h>

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_aton()
#include <stdlib.h>
#include <string.h>

#include "errlib.h"
#include "sockwrap.h"

#define SIZE 31

char *prog_name;


int main(int argc,char** argv){
    if(argc!=4){
        printf("Usage: ip port message");
        return -1;
    }

    int sock;
    struct sockaddr_in saddr;

    char *message;
    int mess_size;
    //message to be sent

    char buffer[SIZE];
    //buffer for receiving message


    fd_set read_set;
    struct timeval tv;
    int times=10;
    //to manage select

    prog_name=argv[0];

    sock=Socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(atoi(argv[2]));//sarebbe argv[2]
    saddr.sin_addr.s_addr=inet_addr(argv[1]);

    mess_size=sizeof(char)*(strlen(argv[3])+1);
    message=malloc(mess_size);
    memcpy(message,argv[3],mess_size);



    //bind(sock,(struct sockaddr*)&saddr,sizeof(sock));
    //sendto(sl,buffer,length,&saddr,sizeof(saddr))
    //sendto (int socket, const void* data, size_t datalen, int flags, const struct sockaddr *addr, socklen_t addrlen)

    Sendto(sock,argv[3],sizeof(argv[3]),0,&saddr,sizeof(sock));
    printf("Message %s sent to %s:%s\n",message,argv[1],argv[2]);

    //preparing stuff for the select
    tv.tv_sec=times;
    tv.tv_usec=0;
    FD_ZERO(&read_set);
    FD_SET(sock,&read_set);


    int s1;
    if(Select(sock+1,&read_set,NULL,NULL,&tv)>0){
        if(FD_ISSET(sock,&read_set){
            s1=sock;
        }
        else{
            printf("This if else has no pratical sense, it's just didattical\n");
        }
        Recvfrom(s1,buffer,SIZE,0,(struct sockaddr*) &saddr,sizeof(sock));
        printf("Message %s received from %s:%s\n in %d seconds",message,argv[1],argv[2],tv.tv_sec);
    }
    else{
        printf("No message from %d in %d seconds",sock,times);
    }




    free(message);
    return 0;
}