#include <nfc.h>

VALUE cNfcDevice;

/*
 * call-seq:
 *  select_passive_target(tag)
 *
 * Select the +tag+ type from the device
 */
static VALUE select_passive_target(VALUE self, VALUE tag)
{
  nfc_device * dev;
  nfc_modulation * mod;
  nfc_target * ti;

  Data_Get_Struct(self, nfc_device, dev);
  Data_Get_Struct(tag, nfc_modulation, mod);

  ti = (nfc_target *)xmalloc(sizeof(nfc_target));

  if (nfc_initiator_select_passive_target(dev, *mod, NULL, 0, ti) ) {
    switch(mod->nmt) {
      case NMT_ISO14443A:
        return Data_Wrap_Struct(cNfcISO14443A, 0, xfree, ti);
        break;
      case NMT_FELICA:
        /* return Data_Wrap_Struct(cNfcFelica, 0, free, ti); */
        return Qnil;
        break;
      default:
        rb_raise(rb_eRuntimeError, "untested type: %d", mod->nmt);
    } 
  }else {
	xfree(ti);
  }

  return Qfalse;
}

/*
 * call-seq:
 *  poll_target(tag, ms)
 *
 * Poll the +tag+ type from the device
 */
static VALUE poll_target(VALUE self, VALUE tag, VALUE poll_nr, VALUE ms)
{
  nfc_device * dev;
  nfc_modulation * mod;
  nfc_target * ti;
  int code;
	int ms_c, poll_nr_c;
  Data_Get_Struct(self, nfc_device, dev);
  Data_Get_Struct(tag, nfc_modulation, mod);

	ms_c = FIX2INT(ms);
	poll_nr_c = FIX2INT(poll_nr);
	
  ti = (nfc_target *)xmalloc(sizeof(nfc_target));

  code = nfc_initiator_poll_target(dev, mod, 1, poll_nr_c, ms_c, ti);

  if (code > 0) {
    switch(mod->nmt) {
      case NMT_ISO14443A:
        return Data_Wrap_Struct(cNfcISO14443A, 0, xfree, ti);
        break;
      case NMT_FELICA:
        return Data_Wrap_Struct(cNfcFelica, 0, xfree, ti);
        break;
      default:
        rb_raise(rb_eRuntimeError, "untested type: %d", mod->nmt);
    }
  }else {
	xfree(ti);
  }

  return INT2NUM(code);
}

/*
 * call-seq:
 *  name
 *
 * Get the name of the tag reader
 */
static VALUE name(VALUE self)
{
  nfc_device * dev;
  Data_Get_Struct(self, nfc_device, dev);

  return rb_str_new2(nfc_device_get_name(dev));
}

/*
 * call-seq:
 *  deselect
 *
 * Deselect the current tag
 */
static VALUE dev_deselect(VALUE self)
{
  nfc_device * dev;
  Data_Get_Struct(self, nfc_device, dev);

  nfc_initiator_deselect_target(dev);

  return self;
}

static VALUE mod_initialize(VALUE self, VALUE type, VALUE baud)
{
  nfc_modulation * mod;

  Data_Get_Struct(self, nfc_modulation, mod);
  mod->nmt = NUM2INT(type);
  mod->nbr = NUM2INT(baud);

  return self;
}

static VALUE mod_alloc(VALUE klass)
{
  nfc_modulation * modulation;

  modulation = xcalloc(1, sizeof(nfc_modulation));

  return Data_Wrap_Struct(klass, NULL, xfree, modulation);
}

static VALUE mod_nmt(VALUE self)
{
  nfc_modulation * mod;

  Data_Get_Struct(self, nfc_modulation, mod);

  return INT2NUM(mod->nmt);
}

static VALUE mod_nbr(VALUE self)
{
  nfc_modulation * mod;

  Data_Get_Struct(self, nfc_modulation, mod);

  return INT2NUM(mod->nbr);
}

static VALUE initiator_init(VALUE self)
{
  nfc_device * dev;
  int err;

  Data_Get_Struct(self, nfc_device, dev);

  err = nfc_initiator_init(dev);
  if (0 == err)
    return Qtrue;

  return INT2NUM(err);
}

void init_device()
{
  VALUE cNfcModulation;
  cNfcDevice = rb_define_class_under(mNfc, "Device", rb_cObject);
  rb_define_method(cNfcDevice, "initiator_init", initiator_init, 0);
  rb_define_method(cNfcDevice, "select_passive_target", select_passive_target, 1);
  rb_define_method(cNfcDevice, "poll_target", poll_target, 3);
  rb_define_method(cNfcDevice, "name", name, 0);
  rb_define_method(cNfcDevice, "deselect", dev_deselect, 0);

  cNfcModulation = rb_define_class_under(cNfcDevice, "Modulation", rb_cObject);

  /* modulation types. */
  rb_define_const(cNfcModulation, "NMT_ISO14443A", INT2NUM(NMT_ISO14443A));
  rb_define_const(cNfcModulation, "NMT_FELICA", INT2NUM(NMT_FELICA));

  /* baud rates */
  rb_define_const(cNfcModulation, "NBR_UNDEFINED", INT2NUM(NBR_UNDEFINED));
  rb_define_const(cNfcModulation, "NBR_106", INT2NUM(NBR_106));
  rb_define_const(cNfcModulation, "NBR_212", INT2NUM(NBR_212));

  rb_define_alloc_func(cNfcModulation, mod_alloc);

  rb_define_method(cNfcModulation, "initialize", mod_initialize, 2);
  rb_define_method(cNfcModulation, "nmt", mod_nmt, 0);
  rb_define_method(cNfcModulation, "nbr", mod_nbr, 0);
}
