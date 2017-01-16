/**
 * @file session.h
 * Session handling.
 */
#ifndef SESSION_H
#define SESSION_H

#include "mhd.h"

struct Session
{
  char *created;
  const char *cookie;
};

struct Session *construct_session(struct MHD_Connection *connection);

int destruct_session(struct Session *session,
                     struct MHD_Response *response);

#endif
