#include "media.h"
#include <iostream>

using namespace std;

extern "C" media_interface *create_media_object() {
  return new media_interface();
}

extern "C" void destroy_media_object(media_interface *object) { delete object; }

media_interface::media_interface() : x(40) {}

void media_interface::DoSomething() { cout << x << endl; }
