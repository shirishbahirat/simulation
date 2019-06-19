#include <cassert>
#include <pthread.h>

#include "producer.h"

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

extern "C" producer *create_producer() { return new producer(); }

producer::producer() : queue_size(32), number_of_commands(10), consumer(NULL) {

  portq *equeue = new portq();
  portq *dqueue = new portq();

  equeue->capacity = 32;
  equeue->consumed = 0;

  pthread_cond_init(&equeue->cond, NULL);
  pthread_mutex_init(&equeue->lock, NULL);

  dqueue->capacity = 32;
  dqueue->consumed = 0;

  pthread_cond_init(&dqueue->cond, NULL);
  pthread_mutex_init(&dqueue->lock, NULL);

  cout << "New Producer" << endl;
  start_producer_thread();
}

void producer::connect(consumer_interface *cons) {
  assert(cons);
  consumer = cons;

  execute();
}

void producer::execute() {
  while (number_of_commands) {

    pthread_mutex_lock(&lock);
    while (equeue->commands.size() >= queue_size)
      pthread_cond_wait(&cond, &lock);

    consumer->enqueue(number_of_commands);

    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);

    cout << "Producer " << number_of_commands << endl;
    --number_of_commands;
  }
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
  /*
Node *item;
command cmmd;
cmmd.dest = 111;
item = (Node *)malloc(sizeof(Node));
item->data = (void *)&cmmd;

while (1) {
  portqEnqueue(inputPort, item);
  moduleExecuteFunction();
  portqEnqueue(outputPort, item);
}
*/

  cout << "Started Producer Thread" << endl;
  return NULL;
}