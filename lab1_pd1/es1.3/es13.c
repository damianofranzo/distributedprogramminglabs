#include <stdlib.h> // getenv()
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h> // timeval
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_aton()
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "errlib.h"
#include "sockwrap.h"

/**
 *	Mannella Luca
 *	Distributed Programming I (03MQPOV)
 *	Academic Year 2014/2015
 *	EXERCISE 1.3 - Simple TCP client
 **/

#define SIZE 20

char *prog_name;
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


int main(int argc, char *argv[]){

	uint16_t port;
	char n[SIZE];
	int sock, i, end=0;
	struct sockaddr_in server_addr;

	prog_name = argv[0];
	if(argc != 3)
		err_quit("Wrong input format!\nThe right format should be: %s <dest_IP_add> <dest_port>\n", argv[0]);

	sock = Socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//Create connection
	port = htons( atoi(argv[2]) );
	server_addr.sin_port = port;
	server_addr.sin_family = AF_INET;
		//convert and set the ip address into the structure
	i = inet_aton(argv[1], &server_addr.sin_addr );
	if(i==0)
		err_quit("Invalid IP address!\n");

	Connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));

	printf("I established the connection with the server %s correctly!\n", argv[1]);
	while(!end) {
		printf("Enter 2 integers (n1 n2): ");
		//scanf("%s", n);			//read data
		fgets(n, SIZE, stdin);
		cleanString(n);

		if(strcmp(n, "end")==0) {	//if are equal broke the loop
			end = 1;
		} else {
			sprintf(n,"%s\r\n", n);
			Write(sock, n, strlen(n)*sizeof(char));		//send data
			i = Read(sock, n, sizeof(n));				//receive data
			cleanString(n);

			if(n[0]>='0' && n[0] <='9')
				printf("The result is = %s\n", n);		//print result
			else
				printf("%s\n", n);
		}
	}
	Close(sock);
	printf("Connection closed!\n");

	return EXIT_SUCCESS;
}
