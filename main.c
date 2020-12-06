#include"queue.h"

int main(void) {
  Queue *queue;
  init_queue(3, queue);
  printf("%d\n", queue->front);
  enqueue(1, queue);
  print_queue(queue);

  return 0;
}

