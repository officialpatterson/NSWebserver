#include "resource.h"
#include <stdlib.h>
#include <string.h>

struct resource{
	int length;
	char * data;
    char * type;
};
char * tokenize(char * string);

Resource * createResource(char * location){
	
	FILE *fileResource =fopen(location, "r");

	Resource * resource = (Resource *) malloc(sizeof(Resource));

	if (fileResource==NULL){
		resource = NULL;
		return resource;
	}   
	

	/*get file size*/
	fseek (fileResource , 0 , SEEK_END);
  	resource->length = ftell (fileResource);
 	rewind (fileResource);

	/*allocate enough memory to the Resource structure and copy the file t te struct*/
	resource->data = (char*) malloc (sizeof(char)*resource->length);
    
	fread(resource->data,1,resource->length,fileResource);
	fclose(fileResource);
    
    resource->type = NULL;

	return resource;
}
char * getResourceData(Resource * r){
	return r->data;
}
int getResourceLength(Resource * r){
	return r->length;
}
void destroyResource(Resource * r){
	free(r);
	r = NULL;
}

