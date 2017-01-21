#include "request.h"

struct Request *construct_request()
{
  struct Request *request = malloc(sizeof(struct Request));
  request->ptr = NULL;
  request->url = NULL;
  request->pp = NULL;
  request->session = NULL;
  return request;
}

void destruct_request(struct Request *request)
{
  if (request == NULL)
  {
    printf("destruct request was NULL\n");
    return;
  }

  if (request->url)
  {
    printf("destruct url free ptr\n");
    destruct_url(request->url);
  }

  if (request->ptr)
  {
    printf("destruct request free ptr\n");
    free(request->ptr);
  }

  if (request->pp)
  {
    printf("destruct request free pp\n");
    MHD_destroy_post_processor(request->pp);
  }

  printf("destruct request free ok\n");
  free(request);
}
