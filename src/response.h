
typedef struct response Response;

Response * createResponse();
char * getResponseStatusString(Response *r);
char * getResponseContentString(Response * r);
void destroyResponse();
