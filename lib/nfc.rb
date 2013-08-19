require 'thread'
require 'nfc/nfc'
require 'nfc/device'
require 'nfc/iso14443a'
require 'nfc/felica'

###
# NFC is a class for dealing with Near Field Communication systems.  This
# library will read RFID tags from an RFID reader.
module NFC
  VERSION = '3.0.0'
end
