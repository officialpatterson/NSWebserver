CFLAGS=-W -Wall -DLINUX -g
OBJECTS=nsserver.o resource.o

NSServer: nsserver.o $(OBJECTS)
gcc -g -o NSServer nesserver.o $(OBJECTS) -lpthread

nsserver.o: src/nsserver.c 
resource.o: src/resource.c src/resource.h

clean:
rm -f *.o NSServer *~
