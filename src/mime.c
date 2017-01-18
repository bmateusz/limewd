#include "mime.h"

static const char *mime_str[] =
{
  "", "text/plain", /* unknown */
  "png", "image/png",
  "jpeg", "image/jpeg",
  "gif", "image/gif",
  "svg", "image/svg+xml",
  "txt", "text/plain",
  "html", "text/html",
  "js", "application/javascript",
  "json", "application/json",
  "css", "text/css",
};

static int hash_mime(const char *ext)
{
  for (int i = MIME_UNKNOWN_T + 2; i < MIME_END_T * 2; i += 2)
  {
    if (strcmp(mime_str[i], ext) == 0)
    {
      return i + 1;
    }
  }
  return MIME_UNKNOWN_T + 1;
}

const char *get_mime(const char *filepath)
{
  int len = strlen(filepath);
  const char *ext = strrchr(filepath, '.');

  if (len > 4 && ext++ != NULL)
  {
    printf("extension is '%s'\n", ext);
    return mime_str[hash_mime(ext)];
  }
  else
  {
    printf("extension is unknown\n");
    return mime_str[MIME_UNKNOWN_T + 1];
  }
}
