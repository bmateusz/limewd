#include "answer.h"

int answer_to_connection(void *cls,
                         struct MHD_Connection *connection,
                         const char *url,
                         const char *method,
                         const char *version,
                         const char *upload_data,
                         size_t *upload_data_size,
                         void **ptr)
{
  char *page;
  struct MHD_Response *response;
  int ret = MHD_NO;

  if (strcmp(method, "GET") == 0)
  {
    if (*ptr == NULL)
    {
      *ptr = connection;
      const char *cookie;
      cookie = MHD_lookup_connection_value(connection,
                                           MHD_COOKIE_KIND,
                                           "session");
      printf("headers passed: <%s>\n", cookie);

      return MHD_YES;
    }
    else
    {
      if (strcmp(url, "/") == 0)
      {
        const char *cookie;
        cookie = MHD_lookup_connection_value(connection,
                                             MHD_COOKIE_KIND,
                                             "session");

        page = (char*)malloc(1024);
        sprintf(page, "<html><body>"
                      "<p>URL: %s</p>"
                      "<p>Method: %s</p>"
                      "<p>Version: %s</p>"
                      "<p>Upload data size %lu</p>"
                      "<p>Cookie: %s</p>"
                      "</body></html>",
                      url,
                      method,
                      version,
                      *upload_data_size,
                      cookie);
        
        response = MHD_create_response_from_buffer(strlen(page),
                                                   (void*)page,
                                                   MHD_RESPMEM_MUST_FREE);

        if (cookie == NULL)
        {
          char session_id[64];
          snprintf(session_id,
                   sizeof(session_id),
                   "session=%X%X%X%X",
                   (unsigned int)rand(),
                   (unsigned int)rand(),
                   (unsigned int)rand(),
                   (unsigned int)rand());

          ret = MHD_add_response_header(response,
                                        MHD_HTTP_HEADER_SET_COOKIE,
                                        session_id);
          printf("set cookie: %d", (int)ret);
        }

        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        printf("respond to %s\n", url);
      }
      else
      {
        const char *notFoundStr = "<html><body>Not found</body></html>";
        response = MHD_create_response_from_buffer(strlen(notFoundStr),
                                                   (void*)notFoundStr,
                                                   MHD_RESPMEM_PERSISTENT);
        if (response)
        {
          ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
          MHD_destroy_response(response);
        }
        else ret = MHD_NO;
      }
      *ptr = NULL;
    }
  }

  if (ret == MHD_NO)
  {
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
  }

  return ret;
}

