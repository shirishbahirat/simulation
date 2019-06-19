#include "container.h"
#include <dlfcn.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

  void *chandle = dlopen("containerlib.so", RTLD_LAZY);

  void (*create_container)();
  create_container = (void (*)())dlsym(chandle, "new_container");
  create_container();

  container *s = container::get_instance();
  container *r = container::get_instance();

  cout << s << " " << s->get_instance_number() << endl;
  cout << r << " " << r->get_instance_number() << endl;

  return 0;
}