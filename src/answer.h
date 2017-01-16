/**
 * @file answer.h
 * Answer to connection.
 */
#ifndef ANSWER_H
#define ANSWER_H

#include "mhd.h"
#include "common.h"
#include "session.h"
#include "static.h"
#include "js.h"
#include "request.h"
#include "auth.h"

/** Answer to connection callback function.
 *
 * It can be called multiple times during a single request.
 * - During the first call only the headers are present.
 * - For the second call we can create the response.
 * - If it was a POST, it can be called several times with upload_data.
 *
 * @param cls custom value selected at registration time
 * @param connection the connection identifying the client
 * @param url the URI called from the client
 * @param method request type, practically POST or GET
 * @param version HTTP version
 * @param upload_data filled in case of POST with upload data
 * @param upload_data filled in case of POST with upload data size
 * @param ptr custom parameter, contains a Request struct after the first call
 * @return MHD_YES on success, MHD_NO on error which causes the connection to terminate
 */
int answer_to_connection(void *cls,
                         struct MHD_Connection *connection,
                         const char *url,
                         const char *method,
                         const char *version,
                         const char *upload_data,
                         size_t *upload_data_size,
                         void **ptr);

#endif
