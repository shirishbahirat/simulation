#include <dlfcn.h>
#include <iostream>

#include "error_mgmt.h"
#include "media.h"
#include "transport.h"

using namespace std;

#define TRANSPORT_IMAGE "transport.so"
#define MEDIA_IMAGE "media.so"
#define ERROR_MGMT_IMAGE "error_mgmt.so"

int main(int argc, const char *argv[]) {

  void *transport = dlopen(TRANSPORT_IMAGE, RTLD_LAZY);
  void *media = dlopen(MEDIA_IMAGE, RTLD_LAZY);
  void *error_mgmt = dlopen(ERROR_MGMT_IMAGE, RTLD_LAZY);

  transport_interface *(*create_transport)();
  void (*destroy_transport)(transport_interface *);

  create_transport =
      (transport_interface * (*)()) dlsym(transport, "create_transport_object");

  destroy_transport = (void (*)(transport_interface *))dlsym(
      transport, "destroy_transport_object");

  transport_interface *trasp = (transport_interface *)create_transport();
  trasp->DoSomething();

  media_interface *(*create_media)();
  void (*destroy_media)(media_interface *);

  create_media = (media_interface * (*)()) dlsym(media, "create_media_object");

  destroy_media =
      (void (*)(media_interface *))dlsym(media, "destroy_media_object");

  media_interface *mdia = (media_interface *)create_media();
  mdia->DoSomething();

  error_mgmt_interface *(*create_error_mgmt)();
  void (*destroy_error_mgmt)(error_mgmt_interface *);

  create_error_mgmt = (error_mgmt_interface * (*)())
      dlsym(error_mgmt, "create_error_mgmt_object");

  destroy_error_mgmt = (void (*)(error_mgmt_interface *))dlsym(
      error_mgmt, "destroy_error_mgmt_object");

  error_mgmt_interface *err_mgmt = (error_mgmt_interface *)create_error_mgmt();
  err_mgmt->DoSomething();

  destroy_transport(trasp);
  destroy_media(mdia);
  destroy_error_mgmt(err_mgmt);
}