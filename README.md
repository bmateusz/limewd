### :lemon: limewd
Lightweight Minimal Ecmascript powered Www Daemon

[![Build Status](https://travis-ci.org/bmateusz/limewd.svg?branch=master)](https://travis-ci.org/bmateusz/limewd)
[![Documentation](https://img.shields.io/badge/docs-latest-brightgreen.svg?style=flat)](https://bmateusz.github.io/limewd)


The goal of this project is to create a general purpose web server.
I develop it in my free time.

Used technologies:
 * libmicrohttpd https://www.gnu.org/software/libmicrohttpd/
 * ((o) Duktape http://duktape.org/
 * SQLite https://www.sqlite.org/
 
### Getting started
Clone the repository and use the `init.sh` script to create your development environment.
```
sudo ./init deb     # Install necessary packages
./init libs         # Download and make libs
sudo ./init install # Install libs
make                # Make project
./lmwd              # Start the server, it uses the www directory
```

Primary target is Ubuntu and Debian Linux, but portability is in mind.
