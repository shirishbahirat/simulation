#include "container.h"
#include <iostream>

using namespace std;

extern "C" void new_container() {

  container *m = container::get_instance();

  cout << m << " lib " << m->get_instance_number() << endl;
}