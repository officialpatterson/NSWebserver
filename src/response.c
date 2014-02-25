#include <stdlib.h>
#include <string.h>
#include "resource.h"
#include "response.h"
#include "request.h"

struct response{
	char * status;
	char * type;
	Resource * resource;
};
char * concat(char * s1, char * s2);

Response * createResponse(Request * request, Resource * resource){
	Response * r = (Response *)malloc(sizeof(Response));
	r->status = "200 OK";
	
	r->resource = createResource(getRequestResourceLocation(request));

	r->type = "image/jpeg";
	return r;
}
char * getResponseStatusString(Response *r){
	char * status = "HTTP/1.1 200 OK\n";

	return status;
}
char * getResponseContentString(Response * r){
	return getResourceData(r->resource);
}
char * getResponseContentLength(Response * r){
    /*create string using the resource length, max content size is 1007 digits long*/
    int resourceLength = getResourceLength(r->resource);
    char * buff = malloc(sizeof(char) * 1024);
    
    snprintf(buff, 1024, "Content-length: %d\n", resourceLength);
    
    return buff;
}
char * getResponseType(Response * r){
    return "Content-Type: image/jpeg\n\n";
}
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}