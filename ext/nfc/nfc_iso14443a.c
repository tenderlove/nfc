#include <nfc_iso14443a.h>

VALUE cNfcISO14443A;

/*
 * call-seq:
 *  uiUidLen
 *
 * Get the uiUidLen
 */
static VALUE uiUidLen(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return INT2NUM(tag->uiUidLen);
}

/*
 * call-seq:
 *  uiAtsLen
 *
 * Get the uiAtsLen
 */
static VALUE uiAtsLen(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return INT2NUM(tag->uiAtsLen);
}

/*
 * call-seq:
 *  abtUid
 *
 * Get the abtUid
 */
static VALUE abtUid(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return rb_str_new(tag->abtUid, tag->uiUidLen);
}

/*
 * call-seq:
 *  abtAts
 *
 * Get the abtAts
 */
static VALUE abtAts(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return rb_str_new(tag->abtAts, tag->uiAtsLen);
}

/*
 * call-seq:
 *  abtAtqa
 *
 * Get the abtAtqa
 */
static VALUE abtAtqa(VALUE self)
{
  tag_info_iso14443a * tag;
  Data_Get_Struct(self, tag_info_iso14443a, tag);

  return rb_str_new(tag->abtAtqa, 2);
}

/*
 * call-seq:
 *  btSak
 *
 * Get the btSak
 */
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
