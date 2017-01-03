#ifndef STATIC_H
#define STATIC_H

#include "common.h"
#include "mime.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int answer_static(struct MHD_Connection *connection,
                  const char *url);

#endif
