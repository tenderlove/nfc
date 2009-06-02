require 'ffi'

class NFC
  class LibNFC # :nodoc
    extend FFI::Library
    ffi_lib 'nfc'

    attach_function :nfc_connect, [], :pointer
    attach_function :nfc_disconnect, [:pointer], :void

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
