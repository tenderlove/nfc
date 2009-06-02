require "test/unit"
require "nfc"

class TestNFC < Test::Unit::TestCase
  def setup
    @nfc = NFC.instance
  end

  def test_connect
    assert_not_nil @nfc.device
  end

  def test_deactivate_field
    @nfc.deactivate_field
  end

  def test_activate_field
    @nfc.activate_field
  end

  def test_crc=
    @nfc.crc = true
    @nfc.crc = false
  end

  def test_parity=
    @nfc.parity = true
    @nfc.parity = false
  end
end
