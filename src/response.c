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
        	printf("type is jpeg");

		r->type =  "Content-Type: image/jpeg\n\n";
    	}
    	else{
		printf("type is not jpeg");
		r->type =  "Content-Type: text/html\n\n";
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


