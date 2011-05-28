#include <nfc_device.h>

static byte_t abtFelica[5] = { 0x00, 0xff, 0xff, 0x00, 0x00 };

/*
 * call-seq:
 *  connect
 *
 * Connect to the NFC device
 */
static VALUE connect(VALUE klass)
{
  nfc_device_t * dev = nfc_connect(NULL);
  if(!dev)
    rb_raise(rb_eRuntimeError, "could not find NFC device");

  if(!nfc_initiator_init(dev))
    rb_raise(rb_eRuntimeError, "oh snap, could not init");

  return Data_Wrap_Struct(klass, 0, 0, dev);
}

/*
 * call-seq:
 *  disconnect
 *
 * Disconnect from the NFC device
 */
static VALUE disconnect(VALUE self)
{
  nfc_device_t * dev;
  Data_Get_Struct(self, nfc_device_t, dev);
  nfc_disconnect(dev);

  return self;
}

/*
 * call-seq:
 *  configure(option, value)
 *
 * Configure the Device with +option+ and +value+
 */
static VALUE configure(VALUE self, VALUE option, VALUE flag)
{
  nfc_device_t * dev;
  Data_Get_Struct(self, nfc_device_t, dev);

  nfc_configure(
    dev,
    (const nfc_device_option_t)NUM2INT(option),
    (const bool)NUM2INT(flag)
  );

  return self;
}

/*
 * call-seq:
 *  select(tag)
 *
 * Select the +tag+ type from the device
 */
static VALUE dev_select(VALUE self, VALUE tag)
{
  nfc_device_t * dev;
  nfc_modulation_t * mod;
  nfc_target_t * ti;

  Data_Get_Struct(self, nfc_device_t, dev);
  Data_Get_Struct(tag, nfc_modulation_t, mod);

  ti = (nfc_target_t *)calloc(1, sizeof(nfc_target_t));

  if (nfc_initiator_select_passive_target(dev, *mod, NULL, 0, ti) ) {
    switch(mod->nmt) {
      case NMT_ISO14443A:
        return Data_Wrap_Struct(cNfcISO14443A, 0, free, ti);
        break;
      case NMT_FELICA:
        return Data_Wrap_Struct(cNfcFelica, 0, free, ti);
        break;
      default:
        rb_raise(rb_eRuntimeError, "untested type: %d", mod->nmt);
    }
  }

  return Qfalse;
}

/*
 * call-seq:
 *  name
 *
 * Get the name of the tag reader
 */
static VALUE name(VALUE self)
{
  nfc_device_t * dev;
  Data_Get_Struct(self, nfc_device_t, dev);

  return rb_str_new2(dev->acName);
}

/*
 * call-seq:
 *  deselect
 *
 * Deselect the current tag
 */
static VALUE dev_deselect(VALUE self)
{
  nfc_device_t * dev;
  Data_Get_Struct(self, nfc_device_t, dev);

  nfc_initiator_deselect_target(dev);

  return self;
}

static VALUE mod_initialize(VALUE self, VALUE type, VALUE baud)
{
  nfc_modulation_t * mod;

  Data_Get_Struct(self, nfc_modulation_t, mod);
  mod->nmt = NUM2INT(type);
  mod->nbr = NUM2INT(baud);

  return self;
}

static VALUE mod_alloc(VALUE klass)
{
  nfc_modulation_t * modulation;

  modulation = xcalloc(1, sizeof(nfc_modulation_t));

  return Data_Wrap_Struct(klass, NULL, xfree, modulation);
}

static VALUE mod_nmt(VALUE self)
{
  nfc_modulation_t * mod;

  Data_Get_Struct(self, nfc_modulation_t, mod);

  return INT2NUM(mod->nmt);
}

static VALUE mod_nbr(VALUE self)
{
  nfc_modulation_t * mod;

  Data_Get_Struct(self, nfc_modulation_t, mod);

  return INT2NUM(mod->nbr);
}

void init_device()
{
  VALUE cNfcModulation;
  VALUE cNfcDevice = rb_define_class_under(cNfc, "Device", rb_cObject);

  rb_define_singleton_method(cNfcDevice, "connect", connect, 0);
  rb_define_method(cNfcDevice, "disconnect", disconnect, 0);
  rb_define_method(cNfcDevice, "configure", configure, 2);
  rb_define_method(cNfcDevice, "select", dev_select, 1);
  rb_define_method(cNfcDevice, "deselect", dev_deselect, 0);
  rb_define_method(cNfcDevice, "name", name, 0);

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
