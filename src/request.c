#include <stdio.h>
#include <stdlib.h>
#include "request.h"
#include <string.h>
struct request{
    char * type;
    char * resourceLocation;
    char * host;
};

Request * createRequest(char * requestText){
    
    Request * r = (Request *)malloc(sizeof(Request));
    
    if(r == NULL){
        //request allocation failed
    }
    
    char * token = strtok(requestText, " ");
    
    while(token != NULL){
        
        if(strncmp(token, "GET", 3) == 0 )
            r->type = token;
        
        if(strncmp(token, "/", 1) == 0){
            r->resourceLocation = token+1;
        }
		token = strtok(NULL, " ");
	}
    
    
    if(r->type == NULL || r->resourceLocation == NULL){
        printf("invalid Request");
    }
    return r;
}
char * getRequestResourceLocation(Request * r){
    
    if(strncmp(r->resourceLocation, "/", 2) == 0 )
        return "index.html";
    else
        return r->resourceLocation;
}
char * getRequestType(Request  * r){
    return r->resourceLocation;
}
char * getRequestHost(Request * r){
    return r->host;
}
void destroy(Request * r){
    r = NULL;
    free(r);
}