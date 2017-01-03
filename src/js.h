#ifndef JS_H
#define JS_H

#include "mhd.h"
#include "duktape.h"
#include "common.h"

int answer_js(struct MHD_Connection *connection,
              const char *url);

#endif
