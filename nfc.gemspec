# -*- encoding: utf-8 -*-
$:.push File.expand_path("../lib", __FILE__)


Gem::Specification.new do |s|
  s.name        = "nfc"
  s.version     = 1.0
  s.platform    = Gem::Platform::RUBY
  s.authors     = ["Aaron Patterson", "Pablo Carranza Velez"]
  s.email       = ["pablocarranza@gmail.com"]
  s.homepage    = ""
  s.summary     = %q{libnfc wrapper}
  s.description = %q{Forked from tenderlove/nfc.}


  s.files         = `git ls-files`.split("\n")

  s.require_paths = ["lib"]
  s.extensions << 'ext/nfc/extconf.rb'
end
