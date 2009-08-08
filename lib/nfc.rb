require 'singleton'
require 'thread'
require 'nfc/nfc'
require 'nfc/device'

class NFC
  VERSION = '1.0.0'

  include Singleton

  def initialize
    @device = nil
    @mutex = Mutex.new
  end

  def deactivate_field
    device.configure Device::DCO_ACTIVATE_FIELD, 0
  end

  def activate_field
    device.configure Device::DCO_ACTIVATE_FIELD, 1
  end

  def crc= value
    device.configure Device::DCO_HANDLE_CRC, value ? 1 : 0
  end

  def parity= v
    device.configure Device::DCO_HANDLE_PARITY, v ? 1 : 0
  end

  def device
    @device ||= connect
  end

  def infinite_list_passive= v
    device.configure Device::DCO_INFINITE_LIST_PASSIVE, v ? 1 : 0
  end

  def poll_mifare
    device.select Device::IM_ISO14443A_106
  end

  def deselect
    device.deselect
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
