#ifndef SESSION_H
#define SESSION_H

#include "mhd.h"

const char *check_or_create_session(struct MHD_Connection *connection,
                                    char **created);

int set_session(char *session,
                struct MHD_Response *response);

#endif
