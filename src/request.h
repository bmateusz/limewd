/**
 * @file request.h
 * Request handling structure.
 */
#ifndef REQUEST_H
#define REQUEST_H

#include "mhd.h"
#include "url.h"

struct Request
{
  void *ptr;
  struct MHD_PostProcessor *pp;
  struct Url *url;
  struct Session *session;
};

struct Request *construct_request();
void destruct_request(struct Request *request);

#endif
