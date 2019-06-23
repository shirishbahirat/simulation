#include <pthread.h>
#include <stdio.h>

pthread_cond_t empty, fill;
pthread_mutex_t lock;

pthread_t prd_thread, cns_thread;

#define COUNT_MAX 3

int count = 0;
int commands = 0;

void *producer(void *arg) {
  while (1) {

    pthread_mutex_lock(&lock);

    while (count == COUNT_MAX)
      pthread_cond_wait(&empty, &lock);

    ++count;
    ++commands;

    if (commands > 10)
      break;

    printf("producer cn %d cm %d\n", count, commands);

    pthread_cond_signal(&fill);

    pthread_mutex_unlock(&lock);
  }

  return NULL;
}

void *consumer(void *arg) {
  while (1) {

    pthread_mutex_lock(&lock);

    while (count == 0)
      pthread_cond_wait(&fill, &lock);

    --count;
    if (commands > 10)
      break;

    printf("consumer cn %d cm %d\n", count, commands);

    pthread_cond_signal(&empty);

    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

int main(int argc, char const *argv[]) {

  pthread_create(&prd_thread, NULL, producer, NULL);
  pthread_create(&cns_thread, NULL, consumer, NULL);

  pthread_join(prd_thread, NULL);
  pthread_join(cns_thread, NULL);

  return 0;
}