#include "mime.h"

// Hash(x) = (x[0] & 15 + x[1] & 67 + len) mod 11
static const char *mime_str[] =
{
  "", "text/plain",
  "jpeg", "image/jpeg",
  "js", "application/javascript",
  "png", "image/png",
  "json", "application/json",
  "txt", "text/plain",
  "svg", "image/svg+xml",
  "css", "text/css",
  "es", "application/ecmascript",
  "gif", "image/gif",
  "html", "text/html",
};

static const int n_mime_str = 11;

static int hash_mime(const char *str)
{
  int len = strlen(str);
  if (len) return ((str[0] & 15) + (str[1] & 67) + len) % 11;
  else return 0;
}

const char *get_mime(const struct Url *url)
{
  printf("extension is '%s'\n", url->ext);
  const char *res = mime_str[hash_mime(url->ext) * 2];
  if (strcmp(res, url->ext) == 0)
  {
    return mime_str[hash_mime(url->ext) * 2 + 1];
  }
  else
  {
    return mime_str[1]; // unknown
  }
}
