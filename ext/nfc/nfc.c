#include <nfc.h>

VALUE cNfc;

void Init_nfc()
{
  cNfc = rb_define_class("NFC", rb_cObject);

  init_device();
  init_iso14443a();
}
