#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "resource.h"
#include "response.h"

#define PORTNUM 8888

struct sockaddr_in sockaddr; /* socket info about our server */
int fd;            /* socket used to listen for incoming connections */
int clientFd;
struct sockaddr_in cliaddr;
socklen_t cliaddr_len = sizeof(cliaddr);
socklen_t socksize = sizeof(struct sockaddr_in);

void initialiseServer();
void runServer();
void stopServer();
void getResource(char * location);
int main(int argc, char *argv[])
{
    
    
    initialiseServer();
    runServer();
    stopServer();
    return 0;
}

void initialiseServer(){
    
    
    sockaddr.sin_family = AF_INET;                /* set the type of connection to TCP/IP */
    sockaddr.sin_addr.s_addr = INADDR_ANY; /* set our address to any interface */
    sockaddr.sin_port = htons(PORTNUM);           /* set the server port number */
    
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(fd == -1){
        printf("error creating socket");
    }
    
    /* bind serv information to mysocket */
    if(bind(fd, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr)) == -1){
        printf("error binding to port");
    }
    
    /* start listening, allowing a queue of up to 10 pending connections */
    if(listen(fd, 10) == -1){
        printf("error listening on port");
    }
}
void runServer(){
    while (1){
        listen(fd, 10);
        
        clientFd = accept(fd, (struct sockaddr *) &cliaddr, &cliaddr_len);

	if(clientFd == -1){
		printf("Error accepting Connection\n");	
	}
        
        printf("The Client is connected...\n");
	
	char buffer[501];
	int requestLength = recv(clientFd, buffer, 500, 0);
	buffer[requestLength] = '\0';
	int type;

	printf("REQUEST: %s \n\n\n", buffer);

	char * token = strtok(buffer, " ");

	while(token != NULL){
        	printf("REQUEST: %s\n", token);
		token = strtok(NULL, " ");
	}


	/*ceate new response instance*/
	Response * response = createResponse();
	Resource * resource = createResource("index.jpeg");


	write(clientFd, getResponseStatusString(response), 16);
        write(clientFd, "Content-length: 5812\n", 21);
        write(clientFd, "Content-Type: image/jpeg\n\n", 26);
        write(clientFd, getResponseContentString(response),getResourceLength(resource));
        close(clientFd);
    }
}

void stopServer(){
    close(fd);
}
