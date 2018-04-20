/*
 * TEMPLATE 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
//#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>


#include "../errlib.h"
#include "../sockwrap.h"


#define N 50
#define LQ 10


#define PROT_ERR -1

#define PROT_GET 1
#define PROT_QUIT 2

#define PROT_ERR_MSG "-ERR\r\n"
#define PROT_ERR_MSG_LEN 6


//#define BUFF_SIZE 1400


char *prog_name;

int getmessage(char *buffer);
int getfilename(char *buf,char *filename,int request_size);
int long_to_string(char *stringl, int size);

int main (int argc, char *argv[])
{
    //checking the usage of the program
    if(argc!=2){
        printf("Usage:program port\n");
        return -1;
    }
    int listening_socket,connection_socket;
    int port;
    struct sockaddr_in saddr,caddr;
    socklen_t  caddrlen;

    char buffer[N];
    int i=0,flag=1;

    //sockwrap.h has to know prog_name declared with extern
    prog_name=argv[0];


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
    saddr.sin_port = htons(((short)port));
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int enable = 1;
    if (setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        printf("setsockopt(SO_REUSEADDR) failed\n");

    Bind(listening_socket,(struct sockaddr*) &saddr, sizeof(saddr));



    printf("Socket created\n");

    Listen(listening_socket,LQ);
    printf("Listening on %d\n",listening_socket);

    while(flag) {
        //Waiting for client connections
        connection_socket = Accept(listening_socket,(struct sockaddr*) &caddr, &caddrlen);
        printf("Connetion accepted on %d\n",connection_socket);
        if (connection_socket < -1) {
            printf("Error in Accept function\n");
            continue;
        }

        //i can assume a request less than integer limit of byte
        int request_size=(int)Recv(connection_socket, buffer, N, 0);
        printf("Buffer received:%s\n",buffer);

        //variable to handle connection
        int keep_conn_on = 1;
        int mess = getmessage(buffer);

        //variables to handles file tranfer
        int fd;
        char filename[N];
        char *buffer_file=NULL;
        struct stat fileinformation;
        size_t file_size,total_size;

        char file_size_string[4],time_stamp_string[4];



        while (keep_conn_on) {
            switch (mess) {
                case PROT_GET:
                    getfilename(buffer,filename,request_size);
                    printf("Client requiring file: %s\n",filename);
                    //fd=open(filename,"r");

                    //get information about file
                    if(stat(buffer,&fileinformation)<0){
                        printf("File not found, closing connection\n");
                        keep_conn_on=0;
                        mess=PROT_ERR;
                        break;
                    }

                    //i allocate a buffer of the total size of the file plus space for +okb1b2..
                    file_size=(size_t)fileinformation.st_size;
                    total_size=file_size+13;
                    buffer_file=malloc(total_size);

                   //Reading the file and sending it
                    read(fd,buffer_file+13,file_size);

                    long_to_string(file_size_string,htonl((int)file_size));
                    long_to_string(time_stamp_string,(int)file_size);
                    strncpy(buffer,"+ok\r",4);
                    strncpy(buffer+5,file_size_string,4);
                    strncpy(buffer+9,file_size_string,4);

                    Send(connection_socket,buffer_file,total_size,0);


                    break;
                case PROT_QUIT:
                    keep_conn_on = 0;
                    printf("Client requested to quit, closing connection\n");
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
            if(buffer_file!=NULL)
                free(buffer_file);

        }

        // the endless loop has to be handled
        i++;
        if(i==5)
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

int getfilename(char *buf,char *filename,int request_size){
    if(filename==NULL|| buf==NULL)
        return -1;
    strncpy(filename,buf+4,strlen(buf)-6);
    filename[strlen(buf)-5]='\0';
    return 0;
}

int long_to_string(char *stringl, int size){
    if(stringl==NULL)
        return -1;
    int n;
    for(int i=0;i<4;i++){
        n=size%256;
        (size-n)/256;
        stringl[i]=(char)n;
    }
    return 0;
};
