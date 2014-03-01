all: nsserver
nsserver: nsserver.o request.o resource.o response.o
	gcc -g nsserver.o resource.o response.o request.o  -o nsserver

nsserver.o: src/nsserver.c
	gcc -c src/nsserver.c

request.o: src/request.c
	gcc -c src/request.c

resource.o: src/resource.c
	gcc -c src/resource.c

response.o: src/response.c
	gcc -c src/response.c
clean:
	rm -rf *o nsserver
