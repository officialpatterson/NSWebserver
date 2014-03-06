#include "resource.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h> // for open
#include <sys/stat.h>
struct resource{
    int length;
    char * data;
    char * type;
};

Resource * createResource(char * location){
	Resource * resource;
    FILE *fileResource;
    
	if(location == NULL)
        return NULL;
    
    if((fileResource =fopen(location, "r")) == NULL)
        return NULL;

    struct stat fs;
    int fd = open(location, O_RDONLY);
    if (fstat(fd, &fs) == -1)
        return NULL;
    int size = fs.st_size;
    
	
    if((resource = (Resource *) malloc(sizeof(Resource))) == NULL)
        return NULL;
    
  	resource->length = size;
    
	/*allocate enough memory to the Resource structure and copy the file to the struct*/
	if((resource->data = (char*) malloc (sizeof(char)*resource->length)) == NULL)
        return NULL;
    
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
	if(r == NULL){
		return;
	}
	free(r->data);
	free(r);
	r = NULL;
}
char * getResourceType(Resource * r){
    return r->type;
}


