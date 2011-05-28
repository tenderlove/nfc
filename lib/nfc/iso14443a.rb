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
    # Get the UID as a hex string
    def to_s join_string = ''
      sprintf((['%02x'] * szUidLen).join(join_string), * uid).upcase
    end

    ###
    # Inspect this tag
    def inspect
      string_ary =
        [ "(NFC) ISO14443A Tag",
          " ATQA (SENS_RES): #{sprintf("%02x  %02x", *atqa)}",
          "    UID (NFCID1): #{to_s '  '}",
          "   SAK (SEL_RES): #{sprintf("%02x", btSak)}"
        ]
      if szAtsLen > 0
        ats = sprintf((['%02x'] * szAtsLen).join('  '), *self.ats)
        string_ary << "       ATS (ATR): #{ats}"
      end
      string_ary.join "\n"
    end
  end
end
