#include <nfc.h>

static VALUE allocate(VALUE klass) {
  nfc_context * context;
  nfc_init(&context);
  return Data_Wrap_Struct(klass, NULL, nfc_exit, context);
}

void init_context()
{
  VALUE cContext = rb_define_class_under(cNfc, "Context", rb_cObject);
  rb_define_alloc_func(cContext, allocate);
}
