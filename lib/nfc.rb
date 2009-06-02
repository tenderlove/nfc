require 'nfc/lib_nfc'

class NFC
  VERSION = '1.0.0'

  attr_reader :device

  def initialize
    @device = nil
  end

  def connect
    @device = NFC::LibNFC::Device.new(NFC::LibNFC.nfc_connect)
  end
end
