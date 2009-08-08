class NFC
  class ISO14443A
    ###
    # Get the unique ID for this tag
    def uid
      abtUid.unpack 'C*'
    end

    ###
    # Get the ATS for this tag
    def ats
      abtAts.unpack 'C*'
    end

    ###
    # Get the atqa
    def atqa
      abtAtqa.unpack 'C*'
    end

    ###
    # Inspect this tag
    def inspect
      uid = sprintf((['%02x'] * uiUidLen).join('  '), *self.uid)

      string_ary =
        [ "(NFC) ISO14443A Tag",
          " ATQA (SENS_RES): #{sprintf("%02x  %02x", *atqa)}",
          "    UID (NFCID1): #{uid}",
          "   SAK (SEL_RES): #{sprintf("%02x", btSak)}"
        ]
      if uiAtsLen > 0
        ats = sprintf((['%02x'] * uiAtsLen).join('  '), *self.ats)
        string_ary << "       ATS (ATR): #{ats}"
      end
      string_ary.join "\n"
    end
  end
end
