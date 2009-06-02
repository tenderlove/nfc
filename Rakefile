# -*- ruby -*-

require 'rubygems'
require 'hoe'
$: << "lib"
require 'nfc'

Hoe.new('nfc', NFC::VERSION) do |p|
  p.developer('Aaron Patterson', 'aaronp@rubyforge.org')
  p.readme_file   = 'README.rdoc'
  p.history_file  = 'CHANGELOG.rdoc'
  p.extra_rdoc_files  = FileList['*.rdoc']
  p.extra_deps      = ['ffi']
end

# vim: syntax=Ruby
