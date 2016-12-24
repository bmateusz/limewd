#include "mime.h"

static const char *mime_str[] =
{
  "image/png",
  "text/plain",
  "text/plain" /* unknown */
};

const char *get_mime(const char *filename)
{
  int len = strlen(filename);

  if (len > 4)
  {
    const char *ext = filename + len - 3;
    printf("extension is '%s'\n", ext);
    return mime_str[MIME_PNG];
  }
  else
  {
    return mime_str[MIME_UNKNOWN_T];
  }
}
