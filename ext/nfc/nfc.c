#include <nfc.h>

VALUE mNfc;

void Init_nfc()
{
  mNfc = rb_define_module("NFC");

  init_context();
  /*
  init_device();
  init_iso14443a();
  init_felica();
  */
}
