#ifndef ANSWER_H
#define ANSWER_H

#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int answer_to_connection(void *cls,
                         struct MHD_Connection *connection,
                         const char *url,
                         const char *method,
                         const char *version,
                         const char *upload_data,
                         size_t *upload_data_size,
                         void **ptr);

#endif
