all: run

run: queue.o main.o
	gcc -Wall -o run queue.o main.o

queue.o: queue.c
	gcc -Wall -c queue.c

main.o: main.c
	gcc -Wall -c main.c

clean:
	rm *.o *.exe a.out