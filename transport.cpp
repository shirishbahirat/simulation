#include "transport.h"
#include <iostream>

using namespace std;

extern "C" transport_interface *create_transport_object() {
  return new transport_interface();
}

extern "C" void destroy_transport_object(transport_interface *object) {
  delete object;
}

transport_interface::transport_interface() : x(20) {}

void transport_interface::DoSomething() { cout << x << endl; }
