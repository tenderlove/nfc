require 'singleton'
require 'thread'
require 'nfc/nfc'
require 'nfc/device'
require 'nfc/iso14443a'

###
# NFC is a class for dealing with Near Field Communication systems.  This
# library will read RFID tags from an RFID reader.  You should start by reading
# NFC#find
class NFC
  VERSION = '2.0.1'

  include Singleton

  ###
  # Create a new NFC class.  This is private, do this instead:
  #   NFC.instance
  def initialize
    @device = nil
    @mutex = Mutex.new
  end

  ###
  # Deactivate the detection field
  def deactivate_field
    device.configure Device::DCO_ACTIVATE_FIELD, 0
  end

  ###
  # Activate the detection field
  def activate_field
    device.configure Device::DCO_ACTIVATE_FIELD, 1
  end

  ###
  # Do CRC checks
  def crc= value
    device.configure Device::DCO_HANDLE_CRC, value ? 1 : 0
  end

  ###
  # Parity checks
  def parity= v
    device.configure Device::DCO_HANDLE_PARITY, v ? 1 : 0
  end

  ###
  # Get the device
  def device
    @device ||= NFC::Device.connect
  end

  ###
  # Block until a passive tag is detected
  def infinite_list_passive= v
    device.configure Device::DCO_INFINITE_LIST_PASSIVE, v ? 1 : 0
  end

  ###
  # Select a tag
  def select
    device.select Device::IM_ISO14443A_106
  end
  alias :detect :select

  ###
  # Deselect a tag
  def deselect
    device.deselect
  end

  # Read your tag and print the info.
  #
  #   p NFC.instance.find
  #
  # NFC#find will return immidiately, which means you should have a tag
  # sitting on the reader when running it.  If you'd like it to block until
  # it detects a tag, give find a block like so:
  #
  #   NFC.instance.find do |tag|
  #     p tag
  #   end
  #
  # You can even run in an infinite loop if you'd like to continually find
  # tags:
  #
  #   loop do
  #     NFC.instance.find do |tag|
  #       p tag
  #     end
  #   end
  def find
    @mutex.lock
    deactivate_field
    self.infinite_list_passive = block_given?
    self.crc = true
    self.parity = true
    activate_field
    tag = detect
    deselect
    @mutex.unlock
    yield tag if block_given?
    tag
  end
end
