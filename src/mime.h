/**
 * @file mime.h
 * Mime type handling.
 */
#ifndef MIME_H
#define MIME_H

#include <string.h>
#include <stdio.h>

enum
{
  MIME_UNKNOWN_T,
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

const char *get_mime(const char *filepath);

#endif
