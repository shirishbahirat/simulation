#include "error_mgmt.h"
#include <iostream>

using namespace std;

extern "C" error_mgmt_interface *create_error_mgmt_object() {
  return new error_mgmt_interface();
}

extern "C" void destroy_error_mgmt_object(error_mgmt_interface *object) {
  delete object;
}

error_mgmt_interface::error_mgmt_interface() : x(80) {}

void error_mgmt_interface::DoSomething() { cout << x << endl; }
