#ifndef COMMON_H
#define COMMON_H

#include "mhd.h"
#include "string.h"

int answer_copy(struct MHD_Connection *connection,
                const char *str);

int answer_304(struct MHD_Connection *connection);

int answer_404(struct MHD_Connection *connection,
               const char *url);

int answer_500(struct MHD_Connection *connection);

#endif
