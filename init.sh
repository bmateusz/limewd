#!/bin/sh

BASEDIR=$(dirname "$0")
LIBMICROHTTPD=libmicrohttpd-0.9.52
SQLITE=sqlite-autoconf-3150100
DUKTAPE=duktape-1.6.0

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
  cd $LIBMICROHTTPD
  ./configure
  make all
  cd ..
fi

if [ -f $SQLITE.tar.gz ]
then
  echo "Skip sqlite"
else
  echo "Download sqlite"
  wget https://www.sqlite.org/2016/$SQLITE.tar.gz
  tar xf $SQLITE.tar.gz
  cd $SQLITE
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
fi

# echo "Clone jsmn"
# git clone https://github.com/zserge/jsmn

# echo "Clone jemalloc"
# git clone https://github.com/jemalloc/jemalloc
