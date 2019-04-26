#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXLINE 1024

int main(){
	struct sockaddr_in servaddr;
	int sockfd, n;
	int readserver;
	char recvline[MAXLINE + 1];
	char * message = "message from client";
	char buffer[MAXLINE] = {0}; 

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Socket creation error \n"); 
        	return -1; 
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(10500);

	if(inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <0){
		printf("\nInvalid address/ Address not supported \n"); 
        	return -1; 
	}

	if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
		printf("\nConnection Failed \n"); 
        	return -1; 
	}

	send(sockfd, message , strlen(message) , 0 ); 
    	readserver= read( sockfd , buffer, 1024); 
    	printf("%s\n",buffer ); 

	exit(0);
}
