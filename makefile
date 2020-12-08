all: server

server: queue.o server.o
	gcc -Wall -o server queue.o server.o

client: queue.o client.o
	gcc -Wall -o client queue.o client.o

main: queue.o main.o
	gcc -Wall -o main queue.o main.o

main.o: main.c
	gcc -Wall -c main.c

queue.o: queue.c
	gcc -Wall -c queue.c

server.o: server.c
	gcc -Wall -c server.c

client.o: client.c
	gcc -Wall -c client.c

clean:
	rm *.o server client