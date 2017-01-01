#ifndef AUTH_H
#define AUTH_H

#include "mhd.h"

int auth_iterator(void *cls,
                  enum MHD_ValueKind kind,
                  const char *key,
                  const char *filename,
                  const char *content_type,
                  const char *transfer_encoding,
                  const char *data, uint64_t off, size_t size);

#endif
