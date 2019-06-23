#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t empty, fill, lock;

pthread_t prd_thread, cns_thread;

#define COUNT_MAX 3

int count = 0;
int commands = 0;

void *producer(void *arg) {
  while (1) {

    sem_wait(&lock);
    sem_wait(&empty);

    ++count;
    ++commands;

    if (commands > 10)
      break;

    printf("producer cn %d cm %d\n", count, commands);

    sem_post(&fill);

    sem_post(&lock);
  }

  return NULL;
}

void *consumer(void *arg) {
  while (1) {

    sem_wait(&lock);
    sem_wait(&empty);

    --count;
    if (commands > 10)
      break;

    printf("consumer cn %d cm %d\n", count, commands);

    sem_post(&empty);

    sem_post(&lock);
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