#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include "resource.h"
#include "response.h"
#include "request.h"

#define PORTNUM 8888

struct sockaddr_in sockaddr; /* socket info about our server */
int fd;            /* socket used to listen for incoming connections */
int clientFd;
struct sockaddr_in cliaddr;
socklen_t cliaddr_len = sizeof(cliaddr);
socklen_t socksize = sizeof(struct sockaddr_in);
pthread_t threads[0];


void initialiseServer();
void * connectionHandler(void * clientFd);
void runServer();

int main(int argc, char *argv[])
{
    initialiseServer();
    runServer();
    close(fd);
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
    printf("SERVER RUNNING...\n");
    while (1){
      
        listen(fd, 10);
        
        clientFd = accept(fd, (struct sockaddr *) &cliaddr, &cliaddr_len);

        if(clientFd == -1){
            printf("Error accepting Connection\n");	
        }
        
        /*create worker thread for this purpose*/
        int rc = pthread_create(&threads[0], NULL, connectionHandler, (void *) (intptr_t)clientFd);
        
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
   
    }
}
void * connectionHandler(void * clientFd){
    
    printf("::NEW CONNECTION on client connection: %i::\n", (intptr_t)clientFd);
    
	int requestLength;
    /*create a new Request*/
    char buffer[501];
   requestLength = read((intptr_t)clientFd, buffer, 500);
    	
    buffer[requestLength] = '\0';
    Request * request = createRequest(buffer);
    Response * response;
    
    Resource * resource = createResource(getRequestResourceLocation(request));
    printf("\tRequested Resource at: %s\n", getRequestResourceLocation(request));
    
    if(resource == NULL){
        printf("\tSending 404 to client...\n");
        write((intptr_t)clientFd, "HTTP/1.1 404 Not Found\n", 23);
        write((intptr_t)clientFd, "Content-Type: text/html\n", 24);
        write((intptr_t)clientFd, "Connection: close\n\n", 19);
        
    }
    else{
        response = createResponse(request, resource);
        
        /*send the response to the client*/
        write((intptr_t)clientFd, getResponseStatusString(response), strlen(getResponseStatusString(response)));
        write((intptr_t)clientFd, getResponseContentLength(response), strlen(getResponseContentLength(response)));
        write((intptr_t)clientFd, getResponseType(response), strlen(getResponseType(response)));
        write((intptr_t)clientFd, getResponseContentString(response), getResourceLength(resource));

	destroyResponse(response);
    }
    destroyResource(resource);
    destroyRequest(request);

    close((intptr_t)clientFd);
    
    pthread_exit(NULL);
}
