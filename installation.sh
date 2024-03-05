#!/bin/bash

# Run autoheader
autoheader

# Run automake
automake --add-missing

# Run autoconf
autoconf

# Configure and make
./configure
make

# Install with elevated privileges
sudo make install

