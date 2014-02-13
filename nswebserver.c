#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    
    struct sockaddr_in sockaddr; /* socket info about our server */
    int fd;            /* socket used to listen for incoming connections */
    socklen_t socksize = sizeof(struct sockaddr_in);
    
    sockaddr.sin_family = AF_INET;                /* set the type of connection to TCP/IP */
    sockaddr.sin_addr.s_addr = INADDR_ANY; /* set our address to any interface */
    sockaddr.sin_port = htons(8080);           /* set the server port number */
    
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(fd == -1){
        //eror
    }
    /* bind serv information to mysocket */
    if(bind(fd, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr)) == -1){
        //error
    }
    
    /* start listening, allowing a queue of up to 1 pending connection */
    listen(fd, 1);
 

    return 0;
}