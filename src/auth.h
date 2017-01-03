#ifndef AUTH_H
#define AUTH_H

#include "mhd.h"
#include <string.h>

struct Auth
{
  char user[128];
  int roles;
};

struct Auth *construct_auth();

int auth_iterator(void *cls,
                  enum MHD_ValueKind kind,
                  const char *key,
                  const char *filename,
                  const char *content_type,
                  const char *transfer_encoding,
                  const char *data, uint64_t off, size_t size);

int auth_user(struct Auth *auth,
              const char *password);

#endif
