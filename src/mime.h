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
  MIME_PNG,
  MIME_TXT,
  MIME_UNKNOWN_T
} mime_t;

const char *get_mime(const char *filename);

#endif
