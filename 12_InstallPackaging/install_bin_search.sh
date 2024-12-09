#!/bin/bash

echo "Running autoreconf"
autoreconf -vfis

echo "Running ./configure --prefix=/usr/local"
./configure --prefix=/usr/local

echo "Running make all install"
echo '\n\n\n' | sudo make all install

echo "Done."
