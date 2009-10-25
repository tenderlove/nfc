#include <nfc_felica.h>

VALUE cNfcFelica;

/*
 * uint32_t uiLen;
 * byte_t btResCode;
 * byte_t abtId[8];
 * byte_t abtPad[8];
 * byte_t abtSysCode[2];
 */

static VALUE uiLen(VALUE self)
{
  tag_info_felica * tag;
  Data_Get_Struct(self, tag_info_felica, tag);

  return INT2NUM(tag->uiLen);
}

static VALUE btResCode(VALUE self)
{
  tag_info_felica * tag;
  Data_Get_Struct(self, tag_info_felica, tag);

  return INT2NUM(tag->btResCode);
}

static VALUE abtId(VALUE self)
{
  tag_info_felica * tag;
  Data_Get_Struct(self, tag_info_felica, tag);

  return rb_str_new(tag->abtId, 8 );
}

static VALUE abtPad(VALUE self)
{
  tag_info_felica * tag;
  Data_Get_Struct(self, tag_info_felica, tag);

  return rb_str_new(tag->abtPad, 8 );
}

static VALUE abtSysCode(VALUE self)
{
  tag_info_felica * tag;
  Data_Get_Struct(self, tag_info_felica, tag);

  return rb_str_new(tag->abtSysCode, 2 );
}

void init_felica()
{
  cNfcFelica = rb_define_class_under(cNfc, "Felica", rb_cObject);

  rb_define_method(cNfcFelica, "uiLen", uiLen, 0);
  rb_define_method(cNfcFelica, "btResCode", btResCode, 0);
  rb_define_method(cNfcFelica, "abtId", abtId, 0);
  rb_define_private_method(cNfcFelica, "abtPad", abtPad, 0);
  rb_define_private_method(cNfcFelica, "abtSysCode", abtSysCode, 0);
}
