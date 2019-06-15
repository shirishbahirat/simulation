#include <cassert>

#include "producer.h"

extern "C" producer *create_producer() { return new producer(); }

producer::producer() : queue_size(32), number_of_commands(10), consumer(NULL) {
  cout << "New Producer" << endl;
}

void producer::connect(consumer_interface *cons) {
  assert(cons);
  consumer = cons;

  execute();
}

void producer::execute() {
  while (number_of_commands) {
    consumer->enqueue(number_of_commands);
    cout << "Producer " << number_of_commands << endl;
    --number_of_commands;
  }
}