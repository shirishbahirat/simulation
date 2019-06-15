#pragma once

#include <iostream>
#include <queue>

#include "interface.h"

using namespace std;

class consumer : public consumer_interface {
public:
  consumer();

  ~consumer() {}

  virtual void enqueue(uint32_t command);

  virtual void connect(producer_interface *prod);

private:
  virtual void execute();

  queue<uint32_t> commands;

  uint32_t queue_size;

  uint32_t number_of_commands;

  producer_interface *producer;
};