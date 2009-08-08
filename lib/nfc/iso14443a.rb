class NFC
  class ISO14443A
    def uid
      abtUid.unpack('C*')
    end

    def ats
      abtAts.unpack('C*')
    end
  end
end
