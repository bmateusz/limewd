#include "url.h"

struct Url *construct_url(const char *url_str)
{
  struct Url *url = malloc(sizeof(struct Url));

  int len = strlen(url_str);
  const char *www = "www";
  const char *index_path = "/index.html";
  if (len < 2)
  {
    len = strlen(index_path);
    url_str = index_path;
  }
  len += strlen(www);
  char *path = malloc(len + 1);
  strncpy(path, www, len);
  url->path = strncat(path, url_str, len - strlen(path));

  const char *ext = strrchr(url_str, '.');
  if (ext == NULL)
  {
    url->ext = NULL;
  }
  else
  {
    url->ext = ext + 1;
  }

  url->url = url_str;

  return url;
}

void destruct_url(struct Url *url)
{
  free(url->path);
  free(url);
}
