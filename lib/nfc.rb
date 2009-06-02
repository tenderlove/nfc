require 'singleton'
require 'nfc/lib_nfc'

class NFC
  VERSION = '1.0.0'

  attr_reader :device

  include Singleton

  def initialize
    @device = NFC::LibNFC::Device.new(NFC::LibNFC.nfc_connect)
    LibNFC.nfc_reader_init(@device.pointer)
  end

  def deactivate_field
    LibNFC.nfc_configure @device.pointer, LibNFC::DCO_ACTIVATE_FIELD, 0
  end

  def activate_field
    LibNFC.nfc_configure @device.pointer, LibNFC::DCO_ACTIVATE_FIELD, 1
  end

  def crc= value
    LibNFC.nfc_configure @device.pointer, LibNFC::DCO_HANDLE_CRC, value ? 1 : 0
  end

  def parity= v
    LibNFC.nfc_configure @device.pointer, LibNFC::DCO_HANDLE_PARITY, v ? 1 : 0
  end
end
