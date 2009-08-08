#include <nfc_iso14443a.h>

VALUE cNfcISO14443A;

void init_iso14443a()
{
  cNfcISO14443A = rb_define_class_under(cNfc, "ISO14443A", rb_cObject);
}
