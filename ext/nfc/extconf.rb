ENV['RC_ARCHS'] = '' if RUBY_PLATFORM =~ /darwin/

# :stopdoc:

require 'mkmf'

LIBDIR      = Config::CONFIG['libdir']
INCLUDEDIR  = Config::CONFIG['includedir']

$CFLAGS << " -O3 -Wall -Wcast-qual -Wwrite-strings -Wconversion -Wmissing-noreturn -Winline"

HEADER_DIRS = [
  # First search /opt/local for macports
  '/opt/local/include',

  # Then search /usr/local for people that installed from source
  '/usr/local/include',

  # Check the ruby install locations
  INCLUDEDIR,

  # Finally fall back to /usr
  '/usr/include',
]

LIB_DIRS = [
  # First search /opt/local for macports
  '/opt/local/lib',

  # Then search /usr/local for people that installed from source
  '/usr/local/lib',

  # Check the ruby install locations
  LIBDIR,

  # Finally fall back to /usr
  '/usr/lib',
]

nfc_dirs = dir_config('nfc', '/opt/local/include', '/opt/local/lib')
unless ["", ""] == nfc_dirs
  HEADER_DIRS.unshift nfc_dirs.first
  LIB_DIRS.unshift nfc_dirs[1]
end

unless find_header('libnfc/libnfc.h', *HEADER_DIRS)
  abort "libnfc is missing.  please install libnfc: http://libnfc.org/"
end

unless find_library('nfc', 'nfc_connect', *LIB_DIRS)
  abort "libnfc is missing.  please install libnfc: http://libnfc.org/"
end

create_makefile('nfc/nfc')

# :startdoc:
