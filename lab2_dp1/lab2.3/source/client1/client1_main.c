/*
 * TEMPLATE 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include <netinet/in.h>


#include "../sockwrap.h"
#include "../errlib.h"


#define GET_MSG "GET "
#define GET_MSG_LEN 4
#define QUIT_MSG "QUIT\r\n"
#define QUIT_MSG_LEN 6
#define END_MSG "\r\n"
#define END_MSG_SIZE 2

#define GET_SERVER_MSG "+OK\r\n"
#define GET_SERVER_MSG_LEN 5
#define ERR_MSG "-ERR\r\n"
#define ERR_MSG_LEN 6


#define MYBUFFSIZE 1400

#define WAITING_TIME 30
#define HEADER_LEN 13

#define SYS_ERR -2
#define PROT_ERR -1
#define PROT_GET 1

char *prog_name;

size_t getFileSize(char *buffer);
int getMessage(char *buffer);

int main (int argc, char *argv[])
{
    //variable to handle connections
    int sock,quit=1;
    struct sockaddr_in serverAddr;
    socklen_t  fromlen;
    struct sockaddr_in from;

    //to be used for programs
    prog_name = argv[0];
    if(argc <3)
        err_quit("Usage: %s <dest_IP_add> <dest_port>\n", argv[0]);

    sock = Socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    fprintf(stdout,"Socket created\n");

    serverAddr.sin_family    = AF_INET;
    serverAddr.sin_port      = htons((uint16_t) atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    Connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    fprintf(stdout,"Connection Established with %s on port %s\n",argv[1],argv[2]);

    //variable to handle file tranfer
    size_t fileNameLength,totlength,filesize;
    char buffer[MYBUFFSIZE],filename[50];
    struct timeval tval;
    fd_set cset;
    FILE *fd;
    int n,r,keep_conn_on=1,mess,remaining;

    //temp
    char file[MYBUFFSIZE];

    //for each file given from commandline i sent request and wait for response
    for(int i=3;i<argc;i++) {
        if ((argv[i] == NULL)) {
            Send(sock, QUIT_MSG, QUIT_MSG_LEN, 0);
        } else if (strlen(argv[i]) < 1) {
            Send(sock, QUIT_MSG, QUIT_MSG_LEN, 0);
        } else {
            fileNameLength = strlen(argv[i]);

            //preparing buffer message
            memcpy(buffer, GET_MSG, GET_MSG_LEN);
            printf("buffer %s\n",buffer);
            memcpy(buffer + GET_MSG_LEN, argv[i], fileNameLength);
            memcpy(buffer + GET_MSG_LEN + fileNameLength,END_MSG,END_MSG_SIZE);

            fprintf(stdout, "Requesting file %.8s, length of name %d\n", buffer + 4, (int)fileNameLength);
            totlength = GET_MSG_LEN + fileNameLength + END_MSG_SIZE;
            Send(sock, buffer, totlength, 0);

            FD_ZERO(&cset);
            FD_SET(sock, &cset);

            tval.tv_sec = WAITING_TIME;
            tval.tv_usec = 0;

            if ((n = select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == -1) {
                ("select() failed\n");
                break;
            }
            if (n > 0) {
                if (FD_ISSET(sock, &cset)) {
                    Recvfrom(sock, buffer, HEADER_LEN, 0, (struct sockaddr *) &from, &fromlen);
                    mess=getMessage(buffer);
                    switch(mess){
                        case PROT_GET:
                            //get size and timestamp
                            filesize=getFileSize(buffer);
                            remaining=filesize;
                            printf("Remaining: %d\n",(int)filesize);
                            fd=fopen(argv[i],"w+");
                            while(remaining>0){
                                r=Recvfrom(sock, buffer, MYBUFFSIZE, 0, (struct sockaddr *) &from, &fromlen);
                                printf("buffer %s\n",buffer);
                                memcpy(file+(filesize-remaining),buffer,r);
                                remaining-=r;
                                fwrite(buffer,1,r,fd);
                            }
                            fclose(fd);
                            //temp
                            printf("file %s",file);

                            break;
                        case PROT_ERR:
                            fprintf(stderr,"error prot\n");
                            quit=0;
                            break;
                        case SYS_ERR:
                            fprintf(stderr,"system error\n");
                            quit=0;
                            break;
                        default:
                            mess=PROT_ERR;

                    }
                }
                else
                    fprintf(stderr, "Error in select\n");



            }
            else
                fprintf(stderr, "No response from the server, closing connection");
        }
    }
    //if no problem happened, send quit
    if(quit) Send(sock, QUIT_MSG, QUIT_MSG_LEN, 0);
    Close(sock);
    //send quit
    return 0;
}

int getMessage(char *buffer){
    if(buffer==NULL){
        return SYS_ERR;
    }
    else if(strncmp(buffer,ERR_MSG,ERR_MSG_LEN)==0){
        return PROT_ERR;
    }
    else if(strncmp(buffer,GET_SERVER_MSG,GET_SERVER_MSG_LEN)==0){
        return PROT_GET;
    } else{
        return SYS_ERR;
    }
}

size_t getFileSize(char *buffer) {
    if (buffer ==NULL) {
        return 0;
    }
    size_t filesize;

    memcpy(&filesize,buffer+5, sizeof(int));
    filesize=ntohl(filesize);
    return filesize;

}