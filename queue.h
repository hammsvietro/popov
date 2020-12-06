#ifndef queue
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue{
  int max_size;
  int front;
  int rear;
  int *arr;
}
Queue;


void init_queue(int size, Queue *queue);
void enqueue(int value, Queue *queue);
int dequeue(Queue *queue);
bool is_empty_queue(Queue *queue);
bool is_full_queue(Queue *queue);
void destroy_queue(Queue *queue);
void print_queue(Queue *queue);

#endif