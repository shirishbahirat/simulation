#include <cassert>
#include <pthread.h>

#include "producer.h"

extern "C" producer *create_producer() { return new producer(); }

producer::producer() : queue_size(32), number_of_commands(0), consumer(NULL) {

  equeue = new portq();
  dqueue = new portq();

  equeue->capacity = 32;
  equeue->consumed = 0;

  pthread_cond_init(&equeue->cond, NULL);
  pthread_mutex_init(&equeue->lock, NULL);

  dqueue->capacity = 32;
  dqueue->consumed = 0;

  pthread_cond_init(&dqueue->cond, NULL);
  pthread_mutex_init(&dqueue->lock, NULL);

  cout << "New Producer " << equeue->capacity << endl;
}

void producer::connect(consumer_interface *cons) {
  assert(cons);
  consumer = cons;
}

void producer::enqueue(cmd *cp) {

  pthread_mutex_lock(&equeue->lock);

  while (equeue->commands.size() >= equeue->capacity)
    pthread_cond_wait(&equeue->cond, &equeue->lock);

  equeue->commands.push(cp);
  cout << "enqueue " << number_of_commands << " " << equeue->commands.size()
       << endl;

  pthread_cond_broadcast(&equeue->cond);
  pthread_mutex_unlock(&equeue->lock);
}

void producer::dequeue() {

  pthread_mutex_lock(&dqueue->lock);
  while ((equeue->commands.size() >= equeue->capacity) ||
         (equeue->commands.size() <= 0))
    pthread_cond_wait(&dqueue->cond, &dqueue->lock);

  cmd *cp = equeue->commands.front();
  cout << "dequeue " << cp->source_id << endl;
  equeue->commands.pop();

  dqueue->commands.push(cp);

  pthread_cond_broadcast(&dqueue->cond);
  pthread_mutex_unlock(&dqueue->lock);
}

void producer::execute() {

  cout << "Producer Execute " << number_of_commands << endl;
  ++number_of_commands;
}

producer::cmd *producer::command_generator() {

  return new cmd(NULL, number_of_commands, 0);
}

bool producer::start_producer_thread() {
  return (pthread_create(&producer_thread, NULL, producer_thread_entry_function,
                         this) == 0);
}

void producer::producer_thread_exit() {
  (void)pthread_join(producer_thread, NULL);
}

void *producer::producer_thread_entry_function(void *module) {
  ((producer *)module)->producer_thread_function(NULL);
  return NULL;
}

void *producer::producer_thread_function(void *arg) {

  cout << "Started Producer Thread " << equeue->capacity << endl;
  cmd *cp = NULL;
  while (number_of_commands < 20) {

    pthread_mutex_lock(&equeue->lock);
    cp = command_generator();
    pthread_cond_signal(&equeue->cond);
    pthread_mutex_unlock(&equeue->lock);

    enqueue(cp);
    execute();
    dequeue();
  }

  return NULL;
}

int main(int argc, char const *argv[]) {

  producer *prod = create_producer();

  prod->start_producer_thread();
  prod->producer_thread_exit();

  return 0;
}
