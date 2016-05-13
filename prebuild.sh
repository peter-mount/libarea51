#!/bin/sh

# Try to determine the os if OS is not defined
if [ -z "$OS" ]
then
    if [ -f /etc/os-release ]
    then
        . /etc/os-release
        OS="$ID"
    fi
fi

# Dependent on the OS ensure we have specific libraries installed
case "$OS" in
    ubuntu)
        echo "Running under Ubuntu"
#        sudo apt-get install -y \
#            libmicrohttpd-dev \
#            libgdchart-gd2-noxpm-dev
        ;;
    debian)
        echo "Running under Debian"
        ;;
    *)
        echo "Unknown OS"
        ;;
esac

autoconf
./configure
