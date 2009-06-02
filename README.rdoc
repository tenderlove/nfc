= NFC

* http://seattlerb.rubyforge.org

== DESCRIPTION:

NFC is a ruby wrapper for the Near Field Communication library.  The Near
Field Communication library works with many USB RFID readers, so this gem
lets you read RFID tags.

== FEATURES/PROBLEMS:

* Only supports ISO1443A tags (MIFARE) tags right now.

== SYNOPSIS:

  require 'nfc'

  # Read your tag and print the info
  p NFC.instance.find

== REQUIREMENTS:

* A USB RFID reader.  I'm using the touchatag[http://touchatag.com].
* ffi
* libnfc

== INSTALL:

* First install libnfc[http://libnfc.org/]
* Make sure libnfc.dylib or libnfc.so is in your library path
* gem install nfc

== LICENSE:

(The MIT License)

Copyright (c) 2009 Aaron Patterson

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
