#!/bin/sh

set -e

BASEDIR=$(dirname "$0")
LIBMICROHTTPD=libmicrohttpd-0.9.52
SQLITE_YEAR=2017
SQLITE=sqlite-autoconf-3160000
DUKTAPE=duktape-2.0.0

cd $BASEDIR

usage()
{
  echo "usage: init.sh [libs] [install] [deb]"
  echo "  libs - Create lib directory, download and make libmicrohttpd, sqlite, duktape."
  echo "  install - Install libmicrohttpd, sqlite. Requires root privileges."
  echo "  deb - Install development environment with apt-get. Requires root privileges and Debian-like OS."
}

libs()
{
  echo "Create lib directory"
  mkdir -p lib
  cd lib

  if [ -f $LIBMICROHTTPD.tar.gz ]
  then
    echo "Skip libmicrohttpd"
  else
    echo "Download libmicrohttpd"
    wget ftp://ftp.gnu.org/gnu/libmicrohttpd/$LIBMICROHTTPD.tar.gz
    tar xf $LIBMICROHTTPD.tar.gz
    mv $LIBMICROHTTPD libmicrohttpd
    cd libmicrohttpd
    ./configure
    make all
    cd ..
  fi

  if [ -f $SQLITE.tar.gz ]
  then
    echo "Skip sqlite"
  else
    echo "Download sqlite"
    wget https://www.sqlite.org/$SQLITE_YEAR/$SQLITE.tar.gz
    tar xf $SQLITE.tar.gz
    mv $SQLITE sqlite
    cd sqlite
    ./configure
    make all
    cd ..
  fi

  if [ -f $DUKTAPE.tar.xz ]
  then
    echo "Skip duktape"
  else
    echo "Download duktape"
    wget http://duktape.org/$DUKTAPE.tar.xz
    tar xf $DUKTAPE.tar.xz
    mv $DUKTAPE duktape
    cd duktape
    make -f Makefile.sharedlibrary
    cd ..
  fi

  cd ..
}

install()
{
  echo "Requires root privileges (sudo ./init.sh install)"
  cd lib

  echo "Install libmicrohttpd"
  cd libmicrohttpd
  make install
  cd ..

  echo "Install sqlite"
  cd sqlite
  make install
  cd ..

  echo "Install duktape"
  cd duktape
  make -f Makefile.sharedlibrary install
  cd ..

  echo "Run ldconfig"
  ldconfig
  cd ..
}

deb()
{
  echo "Requires root privileges (sudo ./init.sh deb)"
  apt-get install build-essential libgcrypt20-dev libgnutls-dev doxygen graphviz exuberant-ctags
}

if [ "$#" -eq 0 ]
then
  usage
fi

while [ "$1" != "" ]
do
  case "$1" in
    install)
      install
    ;;

    libs)
      libs
    ;;

    deb)
      deb
    ;;

    *)
      usage
    ;;
  esac

  shift
done
