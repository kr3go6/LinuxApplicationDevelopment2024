#!/bin/bash

echo "Removing bin_search"
sudo rm -f /usr/local/bin/bin_search

echo "Removing translations"
sudo rm -rf /usr/local/share/locale/ru/LC_MESSAGES/bin_search.mo

echo "Removing doc"
sudo rm -rf /usr/local/share/doc/bin_search

echo "Removing man"
sudo rm -f /usr/local/share/man/man1/bin_search.c.1

echo "Done."
