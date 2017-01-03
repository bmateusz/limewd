#ifndef REQUEST_H
#define REQUEST_H

#include "mhd.h"

struct Request
{
  void *ptr;
  struct MHD_PostProcessor *pp;
};

struct Request *construct_request();
void destruct_request(struct Request *request);

#endif
