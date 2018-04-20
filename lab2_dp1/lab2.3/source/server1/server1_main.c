/*
 * TEMPLATE 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "../errlib.h"
#include "../sockwrap.h"


#define N 50
#define LQ 10


#define PROT_ERR -1

#define PROT_GET 1
#define PROT_QUIT 2

#define PROT_ERR_MSG "-ERR\r\n"
#define PROT_ERR_MSG_LEN 6


char *prog_name;

int getmessage(char *buffer);
int getfilename(char *buf,char *filename);

int main (int argc, char *argv[])
{
    int listening_socket,connection_socket;
    short port;
    struct sockadrr_in saddr,caddr;

    char buffer[N];

    int i=0,flag=1;

    //sockwrap.h has to know prog_name declared with extern
    prog_name=argv[0];

    //checking the usage of the program
    if(argc!=2){
        printf("Usage:Program port\n");
        return -1;
    }

    //convert the char* port into a integer one
    port=atoi(argv[1]);

    //checking the correctness of the port
    if(port>65556){
        printf("Error -> Insert a correct port\n");
        return -1;
    }

    listening_socket=Socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    //assigning the sockaddr_in structure
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listening_socket,(struct sockaddr*) &saddr, sizeof(saddr));

    printf("Socket created\n");
   // printf("Listening on ", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));

    Listen(listening_socket,LQ);

    while(flag) {
        //Waiting for client connections
        connection_socket = Accept(listening_socket, &caddr, sizeof(caddr));
        if (connection_socket < -1) {
            printf("Error in Accept function\n");
            continue;
        }

        Recv(connection_socket, buffer, N, 0);

        int keep_conn_on = 1;
        int mess = getmessage(buffer);
        int fd;
        char filename[N];

        while (keep_conn_on) {
            switch (mess) {
                case PROT_GET:
                    getfilename(buffer,filename);
                   //lettura file ed invio

                    break;
                case PROT_QUIT:
                    keep_conn_on = 0;
                    break;
                case PROT_ERR:
                    printf("Client sent invalid message\n");
                    keep_conn_on=0;
                    Send(connection_socket,PROT_ERR_MSG,PROT_ERR_MSG_LEN,0);
                    break;
                default:    printf("Something strange happened\n");
                    keep_conn_on=0;
            }
            Close(connection_socket);

        }

        // the endless loop has to be handled
        i++;
        if(i==100)
            flag=0;
    }


	return 0;
}

int getmessage(char *buffer){
    if(buffer==NULL)
        return PROT_ERR;
    else if(strlen(buffer)<6)
        return PROT_ERR;

    if(strncmp(buffer,"GET ",4)==0)
        return PROT_GET;
    else if(strncmp(buffer,"QUIT\r\n",6)==0)
        return PROT_QUIT;
    else return PROT_ERR;
}

int getfilename(char *buf,char *filename){
    strncpy(filename,buf+4,strlen(buf)-6);
    return 0;
}
