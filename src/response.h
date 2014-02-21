
typedef struct response Response;

Response * createResponse();
char * getResponseStatusString(Response *r);
char * getResponseContentString(Response * r);
char * getResponseContentLength(Response * r);
char * getResponseType(Response * r);
void destroyResponse();
