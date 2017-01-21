/**
 * @file js.h
 * Answer with server-side JavaScript.
 */
#ifndef JS_H
#define JS_H

#include "mhd.h"
#include "duktape.h"
#include "common.h"
#include "url.h"

int answer_js(struct MHD_Connection *connection,
              struct Url *url);

#endif
