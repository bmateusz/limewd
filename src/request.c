#include "request.h"

struct Request *construct_request()
{
  struct Request *request = malloc(sizeof(struct Request));
  request->ptr = NULL;
  request->pp = NULL;
  return request;
}

void destruct_request(struct Request *request)
{
  if (request == NULL)
  {
    printf("destruct request was NULL\n");
    return;
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
