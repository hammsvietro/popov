#include"queue.h"

int main(void) {
  Queue *queue = init_queue(3);
  enqueue(1, queue);
  enqueue(2, queue);
  enqueue(3, queue);
  print_queue(queue);

  return 0;
}

