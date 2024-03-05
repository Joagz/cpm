#!/bin/bash

# Run autoheader
autoheader

# Run automake
automake --add-missing

# Run autoconf
autoreconf -vfi

# Configure and make
./configure
make

# Install with elevated privileges
sudo make install

