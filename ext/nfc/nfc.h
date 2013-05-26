#ifndef NFC_H
#define NFC_H

#include <ruby.h>
#include <nfc/nfc.h>

extern VALUE cNfc;
extern VALUE cNfcISO14443A;
extern VALUE cNfcFelica;

void init_context();
void init_device();
void init_iso14443a();
void init_felica();

#endif
