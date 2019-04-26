#include <unistd.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#define MAXLINE 1024
int main(){
	struct sockaddr_in servaddr;
	int listenfd, connfd;
	int readclient;
	int addrlen = sizeof(servaddr);
	int opt = 1;
	char buffer[MAXLINE] = {0}; 
    	char *hello = "message back from server";
	

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    	{ 
        	perror("setsockopt"); 
        	exit(EXIT_FAILURE); 
    	} 
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(10500);

	
	if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) 
    	{ 
        	perror("bind failed"); 
        	exit(EXIT_FAILURE); 
    	} 

	if (listen(listenfd, 3) < 0) 
    	{ 
        	perror("listen"); 
        	exit(EXIT_FAILURE); 
    	} 

	for(;;){
		if ((connfd = accept(listenfd, (struct sockaddr *)&servaddr,  (socklen_t*) &addrlen))<0) 
	    	{ 
			perror("accept"); 
			exit(EXIT_FAILURE); 
	    	} 

		readclient = read(connfd, buffer, MAXLINE); 
	    	printf("%s\n",buffer ); 
	    	send(connfd , hello , strlen(hello) , 0 ); 
	} 
    	return 0; 
}
