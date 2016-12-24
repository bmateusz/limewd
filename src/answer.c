#include "answer.h"

static int print_out_key(void *cls, enum MHD_ValueKind kind,
                         const char *key, const char *value)
{
  printf("  %s: %s\n", key, value);
  return MHD_YES;
}

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

      MHD_get_connection_values(connection, MHD_HEADER_KIND, print_out_key, NULL);

      return MHD_YES;
    }
    else
    {
      if (strncmp(url, "/s", 2) == 0)
      {
        ret = answer_static(connection, url, ptr);
      }
      else if (strcmp(url, "/") == 0)
      {
        char *created = NULL;
        const char *cookie = check_or_create_session(connection, &created);

        page = (char*)malloc(1024);
        snprintf(page,
                 1024,
                 "<html><body>"
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

        if (created != NULL) set_session(created, response);

        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        printf("respond to %s\n", url);
      }
      else
      {
        ret = answer_404(connection, url);
      }
      *ptr = NULL;
    }
  }

  if (ret == MHD_NO)
  {
    ret = answer_500(connection);
  }

  return ret;
}
