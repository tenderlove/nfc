require "minitest/autorun"
require "nfc"

module NFC
  class TestContext < Minitest::Test
    def test_init
      assert NFC::Context.new
    end

    def test_list_devices
      ctx = NFC::Context.new
      assert ctx.devices(1)
    end

    def test_open
      ctx = NFC::Context.new
      devs = ctx.devices(1)
      skip "no devs attached" unless devs.length > 0
      dev = ctx.open nil
    end
  end
end
