#include "auth.h"

int auth_iterator(void *cls,
                  enum MHD_ValueKind kind,
                  const char *key,
                  const char *filename,
                  const char *content_type,
                  const char *transfer_encoding,
                  const char *data, uint64_t off, size_t size)
{
  if (cls == NULL)
  {
    printf("iterator cls null\n");
  }

  if (off && !size)
  {
    printf("ignore last iteration\n");
    return MHD_YES;
  }

  printf("key <%s> data <%s> off %ld size %ld\n", key, data, off, size);
  return MHD_YES;
}
