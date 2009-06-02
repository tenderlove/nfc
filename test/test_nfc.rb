require "test/unit"
require "nfc"

class TestNFC < Test::Unit::TestCase
  def test_connect
    nfc = NFC.new
    assert_nil nfc.device
    nfc.connect
    assert_not_nil nfc.device
  end
end
