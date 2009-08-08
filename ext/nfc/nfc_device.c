#include <nfc_device.h>

static VALUE connect(VALUE klass)
{
  dev_info * dev = nfc_connect();
  nfc_initiator_init(dev);

  return Data_Wrap_Struct(klass, 0, 0, dev);
}

static VALUE disconnect(VALUE self)
{
  dev_info * dev;
  Data_Get_Struct(self, dev_info, dev);
  nfc_disconnect(dev);

  return self;
}

void init_device()
{
  VALUE cNfcDevice = rb_define_class_under(cNfc, "Device", rb_cObject);

  rb_define_singleton_method(cNfcDevice, "connect", connect, 0);
  rb_define_method(cNfcDevice, "disconnect", disconnect, 0);
}
