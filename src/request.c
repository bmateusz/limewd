#include "request.h"

void destruct_request(struct Request *request)
{
  if (request == NULL)
  {
    printf("destruct request was NULL\n");
    return;
  }

  if (request->pp)
  {
    printf("destruct request free pp\n");
    MHD_destroy_post_processor(request->pp);
  }

  printf("destruct request free ok\n");
  free(request);
}
