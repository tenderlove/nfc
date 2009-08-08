#include <nfc_iso14443a.h>

VALUE cNfcISO14443A;

static VALUE uiUidLen(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return INT2NUM(tag->uiUidLen);
}

static VALUE uiAtsLen(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return INT2NUM(tag->uiAtsLen);
}

static VALUE abtUid(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return rb_str_new(tag->abtUid, tag->uiUidLen);
}

static VALUE abtAts(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return rb_str_new(tag->abtAts, tag->uiAtsLen);
}

static VALUE abtAtqa(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return rb_str_new(tag->abtAtqa, 2);
}

static VALUE btSak(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return INT2NUM(tag->btSak);
}

void init_iso14443a()
{
  cNfcISO14443A = rb_define_class_under(cNfc, "ISO14443A", rb_cObject);

  rb_define_method(cNfcISO14443A, "uiUidLen", uiUidLen, 0);
  rb_define_method(cNfcISO14443A, "uiAtsLen", uiAtsLen, 0);
  rb_define_method(cNfcISO14443A, "btSak", btSak, 0);

  rb_define_private_method(cNfcISO14443A, "abtUid", abtUid, 0);
  rb_define_private_method(cNfcISO14443A, "abtAts", abtAts, 0);
  rb_define_private_method(cNfcISO14443A, "abtAtqa", abtAtqa, 0);
}
