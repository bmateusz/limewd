/**
 * @file mime.h
 * Mime type handling.
 */
#ifndef MIME_H
#define MIME_H

#include "url.h"

enum
{
  MIME_UNKNOWN_T,
  MIME_ES,
  MIME_PNG,
  MIME_JPG,
  MIME_GIF,
  MIME_SVG,
  MIME_TXT,
  MIME_HTML,
  MIME_JS,
  MIME_JSON,
  MIME_CSS,
  MIME_END_T
} mime_t;

const char *get_mime(const struct Url *url);

#endif
