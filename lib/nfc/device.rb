module NFC
  class Device
    DCO_HANDLE_CRC            = 0x00
    DCO_HANDLE_PARITY         = 0x01
    DCO_ACTIVATE_FIELD        = 0x10
    DCO_INFINITE_LIST_PASSIVE = 0x20

    IM_ISO14443A_106 = Modulation.new Modulation::NMT_ISO14443A,
                                      Modulation::NBR_106

    # Find a tag, blocks until there is a tag available
    def select
      select_passive_target NFC::Device::IM_ISO14443A_106
    end
  end
end
