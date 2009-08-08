#include <nfc_iso14443a.h>

VALUE cNfcISO14443A;

static VALUE uiUidLen(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return INT2NUM(tag->uiUidLen);
}

void init_iso14443a()
{
  cNfcISO14443A = rb_define_class_under(cNfc, "ISO14443A", rb_cObject);

  rb_define_method(cNfcISO14443A, "uiUidLen", uiUidLen, 0);
}
