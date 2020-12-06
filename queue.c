#include "queue.h"

void init_queue(int max_size, Queue *queue) {
  queue = malloc(sizeof(queue));
  queue->max_size = max_size;
  queue->arr = malloc(sizeof(int) * max_size);
  queue->front = queue->rear = -1;
  printf("queue initialized\n");
}

void enqueue(int value, Queue *queue) {

  if(!is_full_queue(queue)) {
    queue->rear = (queue->rear + 1) % queue->max_size;
    if(is_empty_queue(queue)) queue->front = queue->rear;
    queue->arr[queue->rear] = value;
  }
}

int dequeue(Queue *queue) {
  if(is_empty_queue(queue)) {
    printf("Empty queue");
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
  return ((queue->front+1) % queue->max_size == queue->front);
}
void destroy_queue(Queue *queue) {
  free(queue->arr);
  free(queue);
}

void print_queue(Queue *queue) {
  int i;
  for(i = queue->front; i != queue->rear; i = (i + 1) % queue->max_size) {
    printf("%d ", queue->arr[i]);
  }
  printf("\n");
}
