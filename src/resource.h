/*file to allow fetching of server resources in an abstract manner*/
#include <stdio.h>

typedef struct resource Resource;

Resource * createResource(char * location);
char * getResourceData(Resource * r);
int getResourceLength(Resource * r);
void destroyResource(Resource * r);
char * getResourceType(Resource * r);
