/**
 * @file common.h
 * Common responses.
 */
#ifndef COMMON_H
#define COMMON_H

#include "mhd.h"

/** Create response with http code 200, ok, and copy the string.
 *
 * @param connection the connection identifying the client
 * @param str response string
 */
int answer_copy(struct MHD_Connection *connection,
                const char *str);

/** Create response with http code 304, content not modified.
 *
 * @param connection the connection identifying the client
 */
int answer_304(struct MHD_Connection *connection);

/** Create response with http code 404, not found.
 *
 * @param connection the connection identifying the client
 * @param url the URI called from the client
 */
int answer_404(struct MHD_Connection *connection,
               const char *url);

/** Create response with http code 500, internal server error.
 *
 * @param connection the connection identifying the client
 */
int answer_500(struct MHD_Connection *connection);

#endif
