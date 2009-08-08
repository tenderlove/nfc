require 'singleton'
require 'thread'
#require 'nfc/lib_nfc'
require 'nfc/nfc'

class NFC
  VERSION = '1.0.0'

  include Singleton

  def initialize
    @device = nil
    @mutex = Mutex.new
  end

  def deactivate_field
    LibNFC.nfc_configure device.pointer, LibNFC::DCO_ACTIVATE_FIELD, 0
  end

  def activate_field
    LibNFC.nfc_configure device.pointer, LibNFC::DCO_ACTIVATE_FIELD, 1
  end

  def crc= value
    LibNFC.nfc_configure device.pointer, LibNFC::DCO_HANDLE_CRC, value ? 1 : 0
  end

  def parity= v
    LibNFC.nfc_configure device.pointer, LibNFC::DCO_HANDLE_PARITY, v ? 1 : 0
  end

  def device
    @device ||= connect
  end

  def infinite_list_passive= v
    LibNFC.nfc_configure(
      device.pointer,
      LibNFC::DCO_INFINITE_LIST_PASSIVE,
      v ? 1 : 0
    )
  end

  def poll_mifare
    thing = LibNFC::ISO1443A.new
    LibNFC.nfc_initiator_select_tag(
      device.pointer,
      LibNFC::IM_ISO14443A_106,
      nil,
      0,
      thing
    )
    thing
  end

  def deselect
    LibNFC.nfc_initiator_deselect_tag(device.pointer)
  end

  def find
    @mutex.lock
    deactivate_field
    self.infinite_list_passive = block_given?
    self.crc = true
    self.parity = true
    activate_field
    tag = poll_mifare
    deselect
    disconnect
    @mutex.unlock
    yield tag if block_given?
    tag
  end

  private
  def connect
    NFC::Device.connect
  end

  def disconnect
    device.disconnect
  end
end
