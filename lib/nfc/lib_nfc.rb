require 'ffi'

class NFC
  class LibNFC # :nodoc
    extend FFI::Library
    ffi_lib 'nfc'

    attach_function :nfc_connect, [], :pointer
    attach_function :nfc_disconnect, [:pointer], :void
    attach_function :nfc_reader_init, [:pointer], :int
    attach_function :nfc_configure, [:pointer, :int, :int], :int

    DCO_HANDLE_CRC      = 0x00
    DCO_HANDLE_PARITY   = 0x01
    DCO_ACTIVATE_FIELD  = 0x10

    class Device < FFI::Struct
      layout(:name, [:char, 256])

      def name
        pointer.read_string
      end

      def self.release ptr
        LibNFC.nfc_disconnect ptr
      end
    end
  end
end
