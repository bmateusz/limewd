#!/bin/sh

set -e

BASEDIR=$(dirname "$0")
LIB_SRC_DIR=external
LIB_BIN_DIR=compiled
LIBMICROHTTPD=libmicrohttpd-0.9.52
SQLITE_YEAR=2017
SQLITE=sqlite-autoconf-3160000
DUKTAPE=duktape-2.0.1

cd $BASEDIR

usage()
{
  echo "usage: init.sh [local] [libs] [install] [deb] [get-deps]"
  echo "  local - Configure library install path to local dir."
  echo "  libs - Create $LIB_SRC_DIR directory, download and make libmicrohttpd, sqlite, duktape."
  echo "  install - Install libmicrohttpd, sqlite. Can requires root privileges, see parameter local."
  echo "  deb - Install development environment with apt-get. Requires root privileges and Debian-like OS."
  echo "  get-deps - Install development libraries with apt-get. Requires root privileges and Debian-like OS."
}

libs()
{
  echo "Create $LIB_SRC_DIR directory"
  mkdir -p $LIB_SRC_DIR
  cd $LIB_SRC_DIR

  if [ -f $LIBMICROHTTPD.tar.gz ]
  then
    echo "Skip libmicrohttpd"
  else
    echo "Download libmicrohttpd"
    wget ftp://ftp.gnu.org/gnu/libmicrohttpd/$LIBMICROHTTPD.tar.gz
    tar xf $LIBMICROHTTPD.tar.gz
    mv $LIBMICROHTTPD libmicrohttpd
    cd libmicrohttpd
    ./configure $CONFIGURE_FLAGS
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
    ./configure $CONFIGURE_FLAGS
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
    if [ -n $INSTALL_LIB_PATH ]
    then
      # Duktape lacks configure script, so set the install dir if needed
      sed -i "s:INSTALL_PREFIX=.*:INSTALL_PREFIX=$INSTALL_LIB_PATH:g" Makefile.sharedlibrary
    fi
    make -f Makefile.sharedlibrary
    cd ..
  fi

  cd ..
}

install_local()
{
  mkdir -p $LIB_BIN_DIR
  INSTALL_LIB_PATH="$(pwd)/$LIB_BIN_DIR"
  CONFIGURE_FLAGS="--prefix=$INSTALL_LIB_PATH"
  echo "Configure flags set to: $CONFIGURE_FLAGS"
}

install()
{
  echo "Use parameter 'local' before, otherwise it requires root privileges (sudo ./init.sh install)"
  cd $LIB_SRC_DIR

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

  echo "Run ldconfig if needed"
  if [ -n $INSTALL_LIB_PATH ]
  then
    echo "To use local libraries, run the following command:"
    echo "  export LIBRARY_PATH=$INSTALL_LIB_PATH/lib"
    echo "  export LD_LIBRARY_PATH=$INSTALL_LIB_PATH/lib"
    echo "  export C_INCLUDE_PATH=$INSTALL_LIB_PATH/include"
  fi

  cd ..
}

deb()
{
  echo "Requires root privileges (sudo ./init.sh deb)"
  apt-get install build-essential libgcrypt-dev libgnutls-dev doxygen graphviz exuberant-ctags
}

get_deps()
{
  echo "Requires root privileges (sudo ./init.sh get-deps)"
  apt-get install libmicrohttpd-dev libsqlite3-dev duktape-dev libgcrypt-dev libgnutls-dev doxygen graphviz
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

    get-deps)
      get_deps
    ;;

    local)
      install_local
    ;;

    *)
      usage
    ;;
  esac

  shift
done
