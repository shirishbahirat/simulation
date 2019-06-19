#include <dlfcn.h>
#include <iostream>

#include "consumer.h"
#include "interface.h"
#include "producer.h"

int main(int argc, char const *argv[]) {

  void *phandle = dlopen("libproducer.dylib", RTLD_LAZY);
  // void *phandle = dlopen("producer.so", RTLD_LAZY);
  void *chandle = dlopen("consumer.so", RTLD_LAZY);

  producer *(*create_producer)();
  create_producer = (producer * (*)()) dlsym(phandle, "create_producer");
  producer *prod = (producer *)create_producer();

  consumer *(*create_consumer)();
  create_consumer = (consumer * (*)()) dlsym(chandle, "create_consumer");
  consumer *cons = (consumer *)create_consumer();

  cons->connect(prod);
  prod->connect(cons);

  return 0;
}