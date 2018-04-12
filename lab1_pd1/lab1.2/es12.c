
#include <sys/types.h>
#include <sys/socket.h>
#include "sockwrap.h"



//it has to be declared outside, to be linked with the *proo_name var of sockwrap.c
char *prog_name;

int main(int argc, char** argv){
    int socketc=Socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);



}



