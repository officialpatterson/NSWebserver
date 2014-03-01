#include <stdlib.h>
#include <string.h>
#include "resource.h"
#include "response.h"
#include "request.h"

struct response{
	char * status;
	char * type;
	char * length;
	Resource * resource;
};
Response * createResponse(Request * request, Resource * resource){
	Response * r = (Response *)malloc(sizeof(Response));
	r->status = "HTTP/1.1 200 OK\n";
	
	r->resource = resource;

	/*create the response type*/
	char * resourceType = getResourceType(r->resource);
 
    	if(resourceType != NULL && (strcmp(resourceType, "jpeg") == 0 || strcmp(resourceType, "jpg") == 0)){
            r->type =  "Content-Type: image/jpeg\n\n";
    	}
    	else if(resourceType != NULL && (strcmp(resourceType, "html") == 0 || strcmp(resourceType, "htm") == 0)){
		r->type =  "Content-Type: text/html\n\n";
    	}
        else if(resourceType != NULL && (strcmp(resourceType, "gif") == 0)){
            r->type =  "Content-Type: image/gif\n\n";
    	}
        else{
            r->type =  "Content-Type: application/octet-stream\n\n";
        }

	/*create the content length*/
	int resourceLength = getResourceLength(r->resource);
    	r->length = malloc(sizeof(char) * resourceLength+18);
    	snprintf(r->length, resourceLength+18, "Content-length: %d\n", resourceLength);

	return r;
}
char * getResponseStatusString(Response *r){
	return r->status;
}
char * getResponseContentString(Response * r){
	return getResourceData(r->resource);
}
char * getResponseContentLength(Response * r){
    /*create string using the resource length, max content size is 1007 digits long*/
	return r->length;
}
char * getResponseType(Response * r){

	return r->type;
}
void destroyResponse(Response * r){
	free(r->length);	
	free(r);
}


