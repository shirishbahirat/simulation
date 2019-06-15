#pragma once

#include <iostream>

using namespace std;

class producer_interface;

class consumer_interface {
public:
  virtual void connect(producer_interface *prod) = 0;
  virtual void enqueue(uint32_t command) = 0;
};

class producer_interface {
public:
  virtual void connect(consumer_interface *cons) = 0;
};
