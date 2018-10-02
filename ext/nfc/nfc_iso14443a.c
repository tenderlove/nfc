#include <nfc.h>

VALUE cNfcISO14443A;

/*
 * call-seq:
 *  szUidLen
 *
 * Get the szUidLen
 */
static VALUE szUidLen(VALUE self)
{
    nfc_target * tag;
    Data_Get_Struct(self, nfc_target, tag);

    return INT2NUM(tag->nti.nai.szUidLen);
}

/*
 * call-seq:
 *  szAtsLen
 *
 * Get the szAtsLen
 */
static VALUE szAtsLen(VALUE self)
{
    nfc_target * tag;
    Data_Get_Struct(self, nfc_target, tag);

    return INT2NUM(tag->nti.nai.szAtsLen);
}

/*
 * call-seq:
 *  abtUid
 *
 * Get the abtUid
 */
static VALUE abtUid(VALUE self)
{
    nfc_target * tag;
    Data_Get_Struct(self, nfc_target, tag);

    return rb_str_new((const char *)tag->nti.nai.abtUid, tag->nti.nai.szUidLen);
}

/*
 * call-seq:
 *  abtAts
 *
 * Get the abtAts
 */
static VALUE abtAts(VALUE self)
{
    nfc_target * tag;
    Data_Get_Struct(self, nfc_target, tag);

    return rb_str_new((const char *)tag->nti.nai.abtAts, tag->nti.nai.szAtsLen);
}

/*
 * call-seq:
 *  abtAtqa
 *
 * Get the abtAtqa
 */
static VALUE abtAtqa(VALUE self)
{
    nfc_target * tag;
    Data_Get_Struct(self, nfc_target, tag);

    return rb_str_new((const char *)tag->nti.nai.abtAtqa, 2);
}

/*
 * call-seq:
 *  btSak
 *
 * Get the btSak
 */
static VALUE btSak(VALUE self)
{
    nfc_target * tag;
    Data_Get_Struct(self, nfc_target, tag);

    return INT2NUM(tag->nti.nai.btSak);
}

void init_iso14443a()
{
    cNfcISO14443A = rb_define_class_under(mNfc, "ISO14443A", rb_cObject);

    rb_define_method(cNfcISO14443A, "szUidLen", szUidLen, 0);
    rb_define_method(cNfcISO14443A, "szAtsLen", szAtsLen, 0);
    rb_define_method(cNfcISO14443A, "btSak", btSak, 0);

    rb_define_private_method(cNfcISO14443A, "abtUid", abtUid, 0);
    rb_define_private_method(cNfcISO14443A, "abtAts", abtAts, 0);
    rb_define_private_method(cNfcISO14443A, "abtAtqa", abtAtqa, 0);
}

/* vim: set noet sws=4 sw=4: */
