#include "resource.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
struct resource{
    int length;
    char * data;
    char * type;
};
const char *get_filename_ext(const char *filename);

Resource * createResource(char * location){
	
	if(location == NULL){
        printf("default page");
    }
    
    
    FILE *fileResource =fopen(location, "r");
    
    if (fileResource == NULL)
    {
        int errnum = errno;
        fprintf(stderr, "\tError opening file: %s\n", strerror( errnum ));
        return NULL;
    }

	Resource * resource = (Resource *) malloc(sizeof(Resource));
	/*get file size*/
	fseek (fileResource , 0 , SEEK_END);
  	resource->length = ftell (fileResource);
 	rewind (fileResource);
    
	/*allocate enough memory to the Resource structure and copy the file to the struct*/
	resource->data = (char*) malloc (sizeof(char)*resource->length);
    
	fread(resource->data,1,resource->length,fileResource);
	fclose(fileResource);
    
    resource->type = strrchr(location, '.');
    resource->type = resource->type + 1;
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
char * getResourceType(Resource * r){
    return r->type;
}


