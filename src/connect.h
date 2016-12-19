#ifndef CONNECT_H
#define CONNECT_H

#ifndef _WIN32
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif

#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_ip_str(const struct sockaddr *sa,
                char *s,
                unsigned int maxlen);

int on_client_connect(void *cls,
                      const struct sockaddr *addr,
                      socklen_t addrlen);

void request_completed(void *cls,
                       struct MHD_Connection *connection,
                       void **con_cls,
                       enum MHD_RequestTerminationCode toe);

#endif
