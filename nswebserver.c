#include <sys/types.h>
#include <sys/socket.h>

struct in_addr {
    in_addr_t       s_addr;
};
struct sockaddr_in {
    uint8_t         sin_len;
    sa_family_t     sin_family;
    in_port_t       sin_port;
    struct in_addr  sin_addr;
    char            sin_pad[16];
};

int main(){
    


    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    
    
    /*Create the socket necessary for listening*/
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(fd == -1){
        //error creating socket
    }
    
    //bind the socket to a port
    if(bind(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1){
        //error
    }
    
    int backlog = 10;
    
    
    if(listen(fd, backlog) == -1){
        
    }
    return 0;
}