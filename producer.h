#pragma once

#include <iostream>
#include <pthread.h>
#include <queue>

#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "interface.h"

using namespace std;

class producer : public producer_interface {
public:
  producer();

  ~producer() {}

  virtual void connect(consumer_interface *cons);

  virtual void *producer_thread_function(void *arg);

  virtual void producer_thread_exit();

  bool start_producer_thread();

private:
  struct cmd {
    void *payload;
    uint32_t source_id;
    uint32_t dest_id;

    cmd(void *p, uint32_t s, uint32_t d)
        : payload(p), source_id(s), dest_id(d) {}
  };

  struct portq {

    queue<cmd *> commands;

    uint32_t capacity;
    uint32_t consumed;

    pthread_mutex_t lock;

    pthread_cond_t cond;
  };

  cmd *command;

  portq *equeue;

  portq *dqueue;

  uint32_t queue_size;

  uint32_t number_of_commands;

  consumer_interface *consumer;

  pthread_mutex_t lock;

  pthread_cond_t cond;

  pthread_t producer_thread;

  static void *producer_thread_entry_function(void *module);

  virtual void execute();

  virtual void enqueue(cmd *cp);

  virtual void dequeue();

  virtual cmd *command_generator();
};