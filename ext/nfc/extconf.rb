ENV['RC_ARCHS'] = '' if RUBY_PLATFORM =~ /darwin/

# :stopdoc:

require 'mkmf'

LIBDIR      = Config::CONFIG['libdir']
INCLUDEDIR  = Config::CONFIG['includedir']
HEADER_DIRS = [ '/usr/local/include', INCLUDEDIR, '/usr/include', ]
LIB_DIRS    = [ '/usr/local/lib', LIBDIR, '/usr/lib', ]

nfc_dirs = dir_config('nfc', HEADER_DIRS, LIB_DIRS)

unless find_header('nfc/nfc.h')
  abort "libnfc is missing.  please install libnfc: http://libnfc.org/"
end

unless find_library('nfc', 'nfc_open')
  abort "libnfc is missing.  please install libnfc: http://libnfc.org/"
end

create_makefile('nfc/nfc')

# :startdoc:
