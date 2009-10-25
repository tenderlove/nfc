class NFC
  class Felica

    def uid
      abtId.unpack 'C*'
    end

    def pad
      abtPad.unpack 'C*'
    end

    def sys_code
      abtSysCode.unpack 'C*'
    end

    def to_s join_string = ''
      sprintf((['%02x'] * 8 ).join(join_string), * uid).upcase
    end

    def inspect
# 78     printf("The following (NFC) Felica tag was found:\n\n");
# 79     printf("%18s","ID (NFCID2): "); print_hex(ti.tif.abtId,8);
# 80     printf("%18s","Parameter (PAD): "); print_hex(ti.tif.abtPad,8);
      pad = sprintf( (['%02x'] * 8 ).join('  '), *self.pad) 
      string_ary = [
        "(NFC) Felica Tag",
        "ID    (NFCID2): #{to_s '  '}",
        "Parameter(PAD): #{pad}"
      ]
      string_ary.join "\n"
    end

  end
end
