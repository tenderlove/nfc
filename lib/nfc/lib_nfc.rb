require 'ffi'

class NFC
  class LibNFC
    extend FFI::Library
    ffi_lib 'nfc'

    attach_function :nfc_connect, [], :pointer
    attach_function :nfc_disconnect, [:pointer], :void
    attach_function :nfc_initiator_init, [:pointer], :int
    attach_function :nfc_initiator_deselect_tag, [:pointer], :int
    attach_function :nfc_configure, [:pointer, :int, :int], :int
    attach_function :nfc_initiator_select_tag, [:pointer, :int, :pointer, :int, :pointer], :int

    DCO_HANDLE_CRC            = 0x00
    DCO_HANDLE_PARITY         = 0x01
    DCO_ACTIVATE_FIELD        = 0x10
    DCO_INFINITE_LIST_PASSIVE = 0x20

    IM_ISO14443A_106    = 0x00

    class Device < FFI::Struct
      layout(
        :pdc, :pointer,
        :name, :pointer
      )
    end

    class ISO1443A < FFI::Struct
      layout(
        :abtAtqa, [:uchar, 2],
        :btSak, :uchar,
        :uiUidLen, :int,
        :abtUid, [:uchar, 10],
        :uiAtsLen, :int,
        :abtAts, [:uchar, 36]
      )

      def uid
        self[:abtUid].to_a.slice(0, self[:uiUidLen])
      end

      def ats
        self[:abtAts].to_a.slice(0, self[:uiAtsLen])
      end

      def inspect
        uid = sprintf((['%02x'] * self[:uiUidLen]).join('  '), *self.uid)

        string_ary =
          [ "(NFC) ISO14443A Tag",
            " ATQA (SENS_RES): #{sprintf("%02x  %02x", *(self[:abtAtqa]))}",
            "    UID (NFCID1): #{uid}",
            "   SAK (SEL_RES): #{sprintf("%02x", self[:btSak])}"
          ]
        if self[:uiAtsLen] > 0
          ats = sprintf((['%02x'] * self[:uiAtsLen]).join('  '), *self.ats)
          string_ary << "       ATS (ATR): #{ats}"
        end
        string_ary.join "\n"
      end
    end
  end
end
