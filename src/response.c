#include <stdlib.h>
#include "resource.h"
#include "response.h"

struct response{
	char * status;
	char * type;
	Resource * resource;
};

Response * createResponse(){
	Response * r = (Response *)malloc(sizeof(Response));
	r->status = "200 OK";
	
	r->resource = createResource("index.jpeg");
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
