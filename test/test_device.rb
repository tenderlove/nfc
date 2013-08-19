require "minitest/autorun"
require "nfc"

module NFC
  class TestDevice < Minitest::Test
    def test_initiator_init
      ctx = NFC::Context.new
      devs = ctx.devices(1)
      skip "no devs attached" unless devs.length > 0
      dev = ctx.open nil
      p dev.initiator_init
      p dev.select_passive_target Device::IM_ISO14443A_106
    end
  end
end
