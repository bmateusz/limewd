#ifndef MYWAY_H
#define MYWAY_H

#include <sys/types.h>
#ifndef _WIN32
#include <sys/select.h>
#include <sys/socket.h>
#else
#include <winsock2.h>
#endif
#include <string.h>
#include <microhttpd.h>
#include <stdio.h>
#include <time.h>

#define PORT 8888

#include "answer.h"
#include "connect.h"

#endif
