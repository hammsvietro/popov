#ifndef queue
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>

typedef struct Queue{
  int max_size;
  int front;
  int rear;
  int *arr;
}
Queue;


Queue* init_queue(int size);
void enqueue(int value, Queue *queue);
int dequeue(Queue *queue);
bool is_empty_queue(Queue *queue);
bool is_full_queue(Queue *queue);
void destroy_queue(Queue *queue);
void print_queue(Queue *queue);
char* get_queue(Queue *queue);
int get_queue_size(Queue *queue);

#endif