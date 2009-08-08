# -*- ruby -*-

require 'rubygems'
require 'hoe'
gem 'rake-compiler', '>= 0.4.1'
require "rake/extensiontask"

HOE = Hoe.spec('nfc') do
  developer('Aaron Patterson', 'aaronp@rubyforge.org')
  self.readme_file   = 'README.rdoc'
  self.history_file  = 'CHANGELOG.rdoc'
  self.extra_rdoc_files  = FileList['*.rdoc']
  self.spec_extras = { :extensions => ["ext/nfc/extconf.rb"] }
  self.rubyforge_name = 'seattlerb'
end

RET = Rake::ExtensionTask.new("nfc", HOE.spec) do |ext|
  ext.lib_dir = File.join('lib', 'nfc')
end

# vim: syntax=Ruby
