/**
 * @file connect.h
 * Connection handler.
 */
#ifndef CONNECT_H
#define CONNECT_H

#ifndef _WIN32
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif

#include "mhd.h"
#include "request.h"

void get_ip_str(const struct sockaddr *sa,
                char *s,
                unsigned int maxlen);

int on_client_connect(void *cls,
                      const struct sockaddr *addr,
                      socklen_t addrlen);

void request_completed(void *cls,
                       struct MHD_Connection *connection,
                       void **ptr,
                       enum MHD_RequestTerminationCode toe);

#endif
