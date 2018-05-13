/*
 * TEMPLATE 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "../errlib.h"
#include "../sockwrap.h"


#define LQ 10


#define PROT_ERR -1

#define PROT_GET 1
#define PROT_QUIT 2

#define PROT_ERR_MSG "-ERR\r\n"
#define PROT_ERR_MSG_LEN 6

#define SERV_ERR 1

#define MYBUFSIZE 1400
#define MYBUFSIZE2 1000
#define MYFILENAMESIZE 150


#define HEADER_LEN 13
/*To do:
 * good stdout
 * */

char *prog_name;

int getmessage(char *buffer);
int getfilename(char *buf,char *filename,int request_size);
int sendfilemyprot(int connSock,int fd);

volatile int flag;
void ctrlCHandler(int sig){
    flag=0;
    fprintf(stdout,"\nRequiring to quit, the connection will be closed after the last connection\n");
}

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

    char buffer[MYBUFSIZE2];
    //int flag=1;
    flag=1;
    signal(SIGINT,ctrlCHandler);

    //sockwrap.h has to know prog_name declared with extern
    prog_name=argv[0];

    //convert the char* port into a integer one
    port=atoi(argv[1]);

    //checking the correctness of the port
    if(port>65536){
        fprintf(stderr,"Error: Insert a correct port, it should be a number less then 65536\n");
        return -1;
    }

    listening_socket=Socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    fprintf(stdout,"Socket Created\n");

    //assigning the sockaddr_in structure
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(((short)port));
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //if the port was closed in a bad way, it should make the port reusable
    int enable = 1;
    if (setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        printf("setsockopt(SO_REUSEADDR) failed\n");

    Bind(listening_socket,(struct sockaddr*) &saddr, sizeof(saddr));
    fprintf(stdout, "Bind executed with success\n");

    Listen(listening_socket,LQ);
    fprintf(stdout,"Listening on %d\n",listening_socket);

    //i can assume a request less than integer limit of byte
    int request_size;


    //variables to handle connection
    int mess,keep_conn_on = 1;

    //variables to handles file transfer
    int fd,timestamp;
    char filename[MYFILENAMESIZE];
    char buffer_informations[HEADER_LEN];
    struct stat fileinformation;
    size_t file_size,total_size;


    while(flag) {
        //Waiting for client connections
        connection_socket = Accept(listening_socket, (struct sockaddr *) &caddr, &caddrlen);
        if (connection_socket < -1) {
            fprintf(stderr,"Error in Accept function\n");
            continue;
        }
        fprintf(stdout,"Connection accepted on %d\n", connection_socket);

        //i assume the connection to be always up, until the client request to quit. When
        //the client want to stop the connection, this variable is set to 0
        keep_conn_on = 1;


        while (keep_conn_on) {

            //Wating messages from the client connected
            request_size = (int) Recv(connection_socket, buffer, MYBUFSIZE2, 0);

            //i inspect first character of the message, in order to get the type of comand
            mess = getmessage(buffer);
            switch (mess) {
                case PROT_GET:
                    if (getfilename(buffer, filename, request_size) < 0) {
                        fprintf(stdout,"Problems with buffer, closing connection\n");
                        keep_conn_on = 0;
                        mess = PROT_ERR;
                        break;
                    }
                    fprintf(stdout,"Client requiring file: %s\n", filename);

                    //get information about file
                    if (stat(filename, &fileinformation) < 0) {
                        fprintf(stdout,"File not found, closing connection\n");
                        keep_conn_on = 0;
                        mess = PROT_ERR;
                        break;
                    }

                    //i allocate a buffer of the size of the first information (+okb1b2..)
                    file_size = (size_t) fileinformation.st_size;
                    total_size = file_size + 13;

                    //Reading the file and sending it
                    fd = open(filename, O_RDONLY);
                    if (fd < 0) {
                        printf("failed to open file\n");
                        mess = PROT_ERR;
                        break;
                    }

                    //changed in order to send correctly all the file for each mb
                    file_size = htonl(file_size);
                    timestamp = htonl((int) fileinformation.st_mtim.tv_sec);

                    strncpy(buffer_informations, "+OK\r\n", 5);
                    memcpy(buffer_informations + 5, &file_size, sizeof(int));
                    memcpy(buffer_informations + 9, &timestamp, sizeof(int));

                    Send(connection_socket, buffer_informations,HEADER_LEN, 0);
                    if(sendfilemyprot(connection_socket,fd)<0){
                        fprintf(stdout,"Error in reading file, closing connection\n");
                        keep_conn_on=0;
                        Close(fd);
                        break;
                    }
                    close(fd);
                    break;
                case PROT_QUIT:
                    keep_conn_on = 0;
                    printf("Client requested to quit, closing connection\n");
                    break;
                default:
                    //mess is set to PROT_ERR
                    mess = PROT_ERR;
            }

            //if some errors happened
            if (mess == PROT_ERR) {
                fprintf(stdout,"Client sent invalid message, closing connection\n");
                keep_conn_on = 0;
                Send(connection_socket, PROT_ERR_MSG, PROT_ERR_MSG_LEN, 0);
            }

        }
        Close(connection_socket);
        }

        fprintf(stdout,"Required to quit, closing listening socket\n");
        Close(listening_socket);

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
    if(request_size<6)
        return -1;
    strncpy(filename,buf+4,request_size-6);
    filename[request_size-6]='\0';
    return 0;
}

int sendfilemyprot(int connSock,int fd){
    int readingSize;
    char buffer[MYBUFSIZE];
    while((readingSize=readn(fd, buffer,MYBUFSIZE))>0) {
        Send(connSock, buffer, readingSize, 0);
    }
    if(readingSize==-1)
        return SERV_ERR;
    return 0;
}








