#ifndef NFC_H
#define NFC_H

#include <ruby.h>
#include <nfc/nfc.h>

extern VALUE cNfc;

void init_context();

#include <nfc_device.h>
#include <nfc_iso14443a.h>
#include <nfc_felica.h>

#endif
