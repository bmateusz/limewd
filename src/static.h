/**
 * @file static.h
 * Answer static response.
 */
#ifndef STATIC_H
#define STATIC_H

#include "common.h"
#include "mime.h"
#include <fcntl.h>
#include <sys/stat.h>

/** Answer to static request.
 *
 * @param connection the connection identifying the client
 * @param url the Url struct with the parsed URI called from the client
 */
int answer_static(struct MHD_Connection *connection,
                  struct Url *url);

#endif
