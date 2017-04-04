/**
 * @file mime.h
 * Mime type handling.
 */
#ifndef MIME_H
#define MIME_H

#include "url.h"

const char *get_mime(const struct Url *url);

#endif
