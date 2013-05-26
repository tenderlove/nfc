# :stopdoc:

require 'mkmf'

dir_config 'libnfc'
pkg_config 'libnfc'

unless find_header('nfc/nfc.h')
  abort "libnfc is missing.  please install libnfc: http://libnfc.org/"
end

unless find_library('nfc', 'nfc_init')
  abort "libnfc is missing.  please install libnfc: http://libnfc.org/"
end

create_makefile('nfc/nfc')

# :startdoc:
