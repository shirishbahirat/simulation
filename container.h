#pragma once

#include <iostream>

class container {
private:
  static container *instance;

  container() : instance_number(-1) {}

public:
  static container *get_instance() {
    if (instance == NULL) {
      instance = new container();
    }

    return instance;
  }

  uint32_t get_instance_number() { return ++instance_number; }

private:
  uint32_t instance_number;
};

container *container::instance = NULL;
