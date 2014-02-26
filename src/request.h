
typedef struct request Request;

Request * createRequest(char * requestText);
char * getRequestResourceLocation(Request * r);
char * getRequestType(Request  * r);
char * getRequestHost(Request * r);
void destroyRequest(Request * r);
