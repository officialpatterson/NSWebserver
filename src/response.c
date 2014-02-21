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

Response * createResponse(Request * request, Resource * resource){
	Response * r = (Response *)malloc(sizeof(Response));
	r->status = "200 OK";
	
	r->resource = createResource(getRequestResourceLocation(request));
    
    if(r->status == NULL)
        //resource not found
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
    return "Content-length: 5812\n";
}
char * getResponseType(Response * r){
    return "Content-Type: image/jpeg\n\n";
}