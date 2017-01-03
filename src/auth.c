#include "auth.h"

struct Auth *construct_auth()
{
  struct Auth *auth = malloc(sizeof(struct Auth));
  auth->user[0] = '\0';
  auth->roles = 0;
  return auth;
}

int auth_iterator(void *cls,
                  enum MHD_ValueKind kind,
                  const char *key,
                  const char *filename,
                  const char *content_type,
                  const char *transfer_encoding,
                  const char *data, uint64_t off, size_t size)
{
  struct Auth *auth = cls;
  if (auth == NULL)
  {
    printf("iterator cls null\n");
    return MHD_NO;
  }

  if (off && !size)
  {
    printf("ignore last iteration\n");
    return MHD_YES;
  }

  printf("key <%s> data <%s> off %ld size %ld\n", key, data, off, size);

  if (strcmp(key, "user") == 0)
  {
    strcpy(auth->user, data);
  }

  if (strcmp(key, "password") == 0)
  {
    auth_user(auth, data);
  }

  return MHD_YES;
}

int auth_user(struct Auth *auth,
              const char *password)
{
  printf("compare user pwd: %s/%s\n", auth->user, password);
  auth->roles = 1;
  return 1;
}
