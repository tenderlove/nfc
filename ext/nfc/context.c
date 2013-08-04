#include <nfc.h>

static VALUE allocate(VALUE klass) {
  nfc_context * context;
  nfc_init(&context);
  return Data_Wrap_Struct(klass, NULL, nfc_exit, context);
}

static VALUE open_dev(VALUE self, VALUE name)
{
  nfc_context * ctx;
  nfc_device * dev;
  VALUE device;

  Data_Get_Struct(self, nfc_context, ctx);

  if (NIL_P(name)) {
    dev = nfc_open(ctx, NULL);
  } else {
    dev = nfc_open(ctx, StringValuePtr(name));
  }

  if (NULL == dev)
    rb_raise(rb_eRuntimeError, "Unable to open the device");

  if(nfc_initiator_init(dev) < 0)
    rb_raise(rb_eRuntimeError, "Could not initialize device");

  device = Data_Wrap_Struct(cNfcDevice, 0, nfc_close, dev);
  rb_iv_set(device, "@context", self);
  return device;
}

static VALUE devices(VALUE self, VALUE len)
{
  nfc_context *ctx;
  nfc_connstring * strs;
  size_t found, i;
  VALUE devs;

  Data_Get_Struct(self, nfc_context, ctx);

  strs = malloc(sizeof(nfc_connstring) * len);

  found = nfc_list_devices(ctx, strs, 10);
  devs = rb_ary_new2(found);
  for (i = 0; i < found; i++) {
    rb_ary_push(devs, rb_str_new2(strs[i]));
  }
  free(strs);
  return devs;
}

void init_context()
{
  VALUE cContext = rb_define_class_under(mNfc, "Context", rb_cObject);
  rb_define_alloc_func(cContext, allocate);

  rb_define_method(cContext, "devices", devices, 1);
  rb_define_method(cContext, "open", open_dev, 1);
}
