#/bin/bash

(cd .. ; rsync --exclude='.git' --exclude ".DS_Store" --exclude ".git*" -rv RFM69_ArduinoPi dietpi: )

ssh dietpi "(cd RFM69_ArduinoPi; aclocal; autoheader; automake --add-missing; autoconf; ./configure; make)"
