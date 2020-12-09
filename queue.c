#include "queue.h"
#include <stdlib.h>

Queue* init_queue(int max_size) {
  Queue *queue = mmap(NULL, sizeof(Queue), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
  queue->max_size = max_size;
  queue->arr = mmap(NULL, sizeof(int) * 100, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
  queue->front = queue->rear = -1;
  printf("queue initialized\n");
  return queue;
}

void enqueue(int value, Queue *queue) {
  if(!is_full_queue(queue)) {
    queue->rear = (queue->rear + 1) % queue->max_size;
    if(is_empty_queue(queue)) queue->front = queue->rear;
    queue->arr[queue->rear] = value;
  } else {
    printf("Queue is full!\n");
  }
}

int dequeue(Queue *queue) {
  if(is_empty_queue(queue)) {
    printf("Empty queue\n");
    return -1;
  }
  
  int pop = queue->arr[queue->front];
  if(queue->front == queue->rear) queue->front = queue->rear = -1;
  else queue -> front = (queue->front + 1) % queue->max_size;
  return pop;
}

bool is_empty_queue(Queue *queue) {
  return queue->front < 0;
}
bool is_full_queue(Queue *queue) {
  return ((queue->rear+1) % queue->max_size == queue->front);
}

int get_queue_size(Queue *queue) {
  return queue->front > queue->rear ? (queue->max_size - queue->front + queue->rear + 1) : (queue->rear - queue->front + 1);
}

void destroy_queue(Queue *queue) {
  free(queue->arr);
  free(queue);
}

void print_queue(Queue *queue) {
  if(is_empty_queue(queue)) {
    printf("Queue is empty\n");
    return;
  }
  printf("FRONT: %d\t", queue->front);
  printf("REAR: %d\t", queue->rear);
  printf("\n");

  int i;
  for(i = queue->front ; i != queue-> rear; i = (i+1) % queue->max_size ) {
    printf("%d ", queue->arr[i]);
  }
  printf("%d\n", queue->arr[queue->rear]);
}

char* get_queue(Queue *queue) {
  int i;
  char *string_queue = malloc(sizeof(char) * 50);
  
  if(is_empty_queue(queue)) return "queue is empty";
  strncat(string_queue, "Queue: [", 8);

  if(get_queue_size(queue) == 1) {
    sprintf(string_queue, "%s%d]\n", string_queue, queue->arr[queue->front]);
    return string_queue;
  }

  for(i = queue->front ; i != queue-> rear; i = (i+1) % queue->max_size ) {
    if(i == queue->front) 
      sprintf(string_queue, "%s%d", string_queue, queue->arr[i]);
    else 
      sprintf(string_queue, "%s, %d", string_queue, queue->arr[i]);
  }

  sprintf(string_queue, "%s, %d]\n", string_queue, queue->arr[queue->rear]);


  return string_queue;
}
