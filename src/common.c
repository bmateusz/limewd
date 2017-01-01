#include "common.h"

int answer_304(struct MHD_Connection *connection)
{
  struct MHD_Response *response;
  int ret = MHD_NO;
  const char *errorStr = "<html><body>Not modified</body></html>";

  response = MHD_create_response_from_buffer(strlen(errorStr),
      (void*)errorStr,
      MHD_RESPMEM_PERSISTENT);

  if (response)
  {
    ret = MHD_queue_response(connection, MHD_HTTP_NOT_MODIFIED, response);
    MHD_destroy_response(response);
  }
  else ret = MHD_NO;
  printf("304 OK\n");
  return ret;
}

int answer_404(struct MHD_Connection *connection,
               const char *url)
{
  struct MHD_Response *response;
  int ret = MHD_NO;
  const char *errorStr = "<html><body>Not found</body></html>";

  response = MHD_create_response_from_buffer(strlen(errorStr),
      (void*)errorStr,
      MHD_RESPMEM_PERSISTENT);

  if (response)
  {
    ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);
  }
  else ret = MHD_NO;
  printf("404 error\n");
  return ret;
}

int answer_500(struct MHD_Connection *connection)
{
  struct MHD_Response *response;
  int ret = MHD_NO;
  const char *errorStr = "<html><body>Internal server error</body></html>";

  response = MHD_create_response_from_buffer(strlen(errorStr),
      (void*)errorStr,
      MHD_RESPMEM_PERSISTENT);

  if (response)
  {
    ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
    MHD_destroy_response(response);
  }
  else ret = MHD_NO;
  printf("500 error\n");
  return ret;
}
