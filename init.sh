#!/bin/sh

set -e

BASEDIR=$(dirname "$0")
LIBMICROHTTPD=libmicrohttpd-0.9.52
SQLITE_YEAR=2017
SQLITE=sqlite-autoconf-3160000
DUKTAPE=duktape-2.0.0

echo "Create lib directory"
cd $BASEDIR
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
fi

if [ "$1" = "install" ]
then
  echo "Install libmicrohttpd"
  cd libmicrohttpd
  make install
  cd ..

  echo "Install sqlite"
  cd sqlite
  make install
  cd ..
fi
