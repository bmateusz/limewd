#ifndef URL_H
#define URL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Url
{
  const char *url;
  const char *ext;
  char *path;
  int mode;
};

struct Url *construct_url(const char *url_str);
void destruct_url(struct Url *url);

#endif
