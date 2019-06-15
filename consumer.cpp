#include <cassert>

#include "consumer.h"

extern "C" consumer *create_consumer() { return new consumer(); }

consumer::consumer() : queue_size(32), number_of_commands(10), producer(NULL) {
  cout << "New Consumer" << endl;
}

void consumer::connect(producer_interface *prod) {
  assert(prod);
  producer = prod;
}

void consumer::enqueue(uint32_t command) {
  commands.push(command);
  execute();
}

void consumer::execute() {
  if (commands.size()) {
    cout << "Consumer " << number_of_commands << endl;
    --number_of_commands;
    commands.pop();
  }
}