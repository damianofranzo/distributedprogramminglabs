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


//#define BUFF_SIZE 1400


/*To do:
 * good stdout
 * wrap into functions
 * use more marco
 * send file on 2mb at time
 * good numbers
 * */

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

    //i can assume a request less than integer limit of byte
    int request_size;


    //variable to handle connection
    int keep_conn_on = 1;
    int mess ;

    //variables to handles file tranfer
    int fd;
    char filename[N];
    char *buffer_file=NULL;
    struct stat fileinformation;
    size_t file_size,total_size;

    char file_size_string[4],time_stamp_string[4];

    while(flag) {
        //Waiting for client connections
        connection_socket = Accept(listening_socket,(struct sockaddr*) &caddr, &caddrlen);
        if (connection_socket < -1) {
            printf("Error in Accept function\n");
            continue;
        }
        printf("Connetion accepted on %d\n",connection_socket);
        keep_conn_on=1;





        while (keep_conn_on) {
            //waiting for commands
            request_size=(int)Recv(connection_socket, buffer,1000, 0);
            mess=getmessage(buffer);
            printf("Buffer received:%s\n",buffer);
            switch (mess) {
                case PROT_GET:
                    if(getfilename(buffer,filename,request_size)<0){
                        printf("Request too short,closing connection\n");
                        keep_conn_on=0;
                        mess=PROT_ERR;
                        break;
                    }
                    printf("Client requiring file: %s\n",filename);
                    //fd=open(filename,"r");

                    //get information about file
                    if(stat(filename,&fileinformation)<0){
                        printf("File not found, closing connection\n");
                        keep_conn_on=0;
                        mess=PROT_ERR;
                        break;
                    }

                    //i allocate a buffer of the total size of the file plus space for +okb1b2..
                    file_size=(size_t)fileinformation.st_size;
                    total_size=file_size+14;
                    buffer_file=malloc(total_size);

                   //Reading the file and sending it
                    fd=open(filename,O_RDONLY);
                    if(fd<0){
                        printf("failed to open file\n");
                        mess=PROT_ERR;
                        break;
                    }

                    //changed in order to send correctly all the file for each mb
                    if(readn(fd,buffer_file+13,file_size)==file_size)
                        printf("file read correctly\n");
                    close(fd);
                    printf("File Information\nfile:%s\n",buffer_file+13);

                    if(long_to_string(file_size_string,htonl((int)file_size))==-1){
                        keep_conn_on=0;
                        break;
                    }
                    file_size=htonl(file_size);
                    //memcpy(file_size_string,&file_size, sizeof(uint32_t));
                //    printf("%s\n",file_size_string);
                  //  printf("%d %d %d %d\n",file_size_string[0],file_size_string[1],file_size_string[2],file_size_string[3]);
                  //  printf("problem here: %d\n",(int)fileinformation.st_mtim.tv_sec);

                /*    if(long_to_string(time_stamp_string,htonl((int)fileinformation.st_mtim.tv_sec))==-1){
                        keep_conn_on=0;
                        break;
                    }*/
                    printf("Timestamp: %d\n",fileinformation.st_mtim.tv_sec);
                    int timestamp=htonl((int)fileinformation.st_mtim.tv_sec);
                    //memcpy(time_stamp_string,&timestamp, sizeof(uint32_t));

                    //printf("what is this: ...%1s %1s %1s %1s...\n",time_stamp_string,time_stamp_string+1,time_stamp_string+2,time_stamp_string+3);
                   // printf("%d %d %d %d\n",time_stamp_string[0],time_stamp_string[1],time_stamp_string[2],time_stamp_string[3]);

                    strncpy(buffer_file,"+OK\r\n",5);
                    memcpy(buffer_file+5,&file_size,sizeof(int));
                    memcpy(buffer_file+9,&timestamp,sizeof(int));

                    /*Send(connection_socket,&file_size,4,0);
                    Send(connection_socket,buffer_file,5,0);
                    Send(connection_socket,&timestamp,4,0);
                    */

                    Send(connection_socket,buffer_file,total_size,0);
                    printf("Sending %s\n",buffer_file);
                    //Send(connection_socket,buffer_file+13,total_size-14,0);

                    printf("File sent successfully\n");
                    break;
                case PROT_QUIT:
                    keep_conn_on = 0;
                    printf("Client requested to quit, closing connection\n");
                    break;
                case PROT_ERR:
                    printf("Client sent invalid message, closing connection\n");
                    keep_conn_on=0;
                    Send(connection_socket,PROT_ERR_MSG,PROT_ERR_MSG_LEN,0);
                    break;
                default:
                    printf("Something strange happened\n");
                    keep_conn_on=0;
            }

            if(mess==PROT_QUIT){
                keep_conn_on = 0;
                printf("Client requested to quit, closing connection\n");
            }
            else if(mess==PROT_ERR){
                printf("Client sent invalid message, closing connection\n");
                keep_conn_on=0;
                Send(connection_socket,PROT_ERR_MSG,PROT_ERR_MSG_LEN,0);
                break;
            }
            else{
                printf("Something strange happened\n");
                keep_conn_on=0;
            }
        }
        free(buffer_file);
        buffer_file=NULL;
        Close(connection_socket);
        if(buffer_file!=NULL)
            free(buffer_file);

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
    if(request_size<6)
        return -1;
    strncpy(filename,buf+4,request_size-6);
    filename[request_size-6]='\0';
    return 0;
}

int long_to_string(char *stringl, int size){
/*    if(stringl==NULL)
        return -1;
    else if (strlen(stringl)<4)
        return -1;*/
    //printf("Given size %d\n",size);
  /*  stringl[0]=(size)&0xff;
    stringl[1]=(size>>8)&0xff;
    stringl[2]=(size>>16)&0xff;
    stringl[3]=(size>>24)&0xff;*/

  memcpy(stringl,&size,4);
   // printf("%d%d%d%d\n",stringl[0],stringl[1],stringl[2],stringl[3]);
    return 0;
};
