#ifndef REQUEST_H
#define REQUEST_H

#include "mhd.h"

struct Request
{
  struct MHD_PostProcessor *pp;
};

void destruct_request(struct Request *request);

#endif
