/**
 * @file auth.h
 * Authentication provider.
 */
#ifndef AUTH_H
#define AUTH_H

#include "mhd.h"
#include "sqlite.h"

/** Struct for authentication. */
struct Auth
{
  /** user name */
  char user[128];

  /** roles granted */
  int roles;
};

/** Constructor of Auth struct. */
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

int init_auth();

#endif
