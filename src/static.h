#ifndef STATIC_H
#define STATIC_H

#include "mhd.h"

struct MHD_Response *answer_static(char *url,
                                   void **ptr);

#endif
