#ifndef MHD_H
#define MHD_H

#include <sys/types.h>
#ifndef _WIN32
#include <sys/select.h>
#include <sys/socket.h>
#else
#include <winsock2.h>
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <microhttpd.h>

#endif
