#include <nfc.h>

static VALUE allocate(VALUE klass) {
  nfc_context * context;
  nfc_init(&context);
  return Data_Wrap_Struct(klass, NULL, nfc_exit, context);
}

static VALUE devices(VALUE self)
{
  nfc_context *ctx;
  nfc_connstring strs[10];
  size_t found, i;
  VALUE devs;

  Data_Get_Struct(self, nfc_context, ctx);

  found = nfc_list_devices(ctx, strs, 10);
  devs = rb_ary_new2(found);
  for (i = 0; i < found; i++) {
    rb_ary_push(devs, rb_str_new2(strs[i]));
  }
  return devs;
}

void init_context()
{
  VALUE cContext = rb_define_class_under(mNfc, "Context", rb_cObject);
  rb_define_alloc_func(cContext, allocate);

  rb_define_method(cContext, "devices", devices, 0);
}
