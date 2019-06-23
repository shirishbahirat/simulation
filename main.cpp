#include <dlfcn.h>
#include <iostream>

#include "consumer.h"
#include "interface.h"
#include "producer.h"

int main(int argc, char const *argv[]) {

  void *phandle = dlopen("libproducer.dylib", RTLD_LAZY);
  // void *phandle = dlopen("producer.so", RTLD_LAZY);
  if (phandle == (void *)0)
    cout << "error in opening phandle" << endl;

  void *chandle = dlopen("consumer.so", RTLD_LAZY);
  if (chandle == (void *)0)
    cout << "error in opening chandle" << endl;

  producer *(*create_producer)();
  create_producer = (producer * (*)()) dlsym(phandle, "create_producer");
  producer *prod = (producer *)create_producer();

  if (prod == NULL) {
    char *err = dlerror();
    if (err != NULL)
      cout << "error in creating producer" << endl;
  }

  consumer *(*create_consumer)();
  create_consumer = (consumer * (*)()) dlsym(chandle, "create_consumer");
  consumer *cons = (consumer *)create_consumer();

  if (cons == NULL) {
    char *err = dlerror();
    if (err != NULL)
      cout << "error in creating consumer" << endl;
  }

  cons->connect(prod);
  prod->connect(cons);

  // dlclose( handle );

  return 0;
}