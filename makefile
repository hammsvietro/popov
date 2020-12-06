all: server

server: queue.o server.o
	gcc -Wall -o server queue.o server.o

client: queue.o client.o
	gcc -Wall -o client queue.o client.o

queue.o: queue.c
	gcc -Wall -c queue.c

server.o: server.c
	gcc -Wall -c server.c

client.o: client.c
	gcc -Wall -c client.c

clean:
	rm *.o server client