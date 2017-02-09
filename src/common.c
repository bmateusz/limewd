#include "common.h"

int answer_copy(struct MHD_Connection *connection,
                const char *str)
{
  struct MHD_Response *response;
  int ret = MHD_NO;

  response = MHD_create_response_from_buffer(strlen(str),
                                             (void*)str,
                                             MHD_RESPMEM_MUST_COPY);

  if (response)
  {
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    ret &= MHD_add_response_header(response, MHD_HTTP_HEADER_CONTENT_TYPE, "text/html");
    MHD_destroy_response(response);
  }
  else ret = MHD_NO;
  printf("200 OK\n");
  return ret;
}

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
               const char *url UNUSED)
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
