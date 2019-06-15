#pragma once

#include <iostream>
#include <queue>

#include "interface.h"

using namespace std;

class producer : public producer_interface {
public:
  producer();

  ~producer() {}

  virtual void connect(consumer_interface *cons);

private:
  virtual void execute();

  queue<uint32_t> commands;

  uint32_t queue_size;

  uint32_t number_of_commands;

  consumer_interface *consumer;
};