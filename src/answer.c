#include "answer.h"

static int print_out_key(void *cls UNUSED,
                         enum MHD_ValueKind kind UNUSED,
                         const char *key,
                         const char *value)
{
  printf("  %s: %s\n", key, value);
  return MHD_YES;
}

int answer_to_connection(void *cls UNUSED,
                         struct MHD_Connection *connection,
                         const char *url,
                         const char *method UNUSED,
                         const char *version UNUSED,
                         const char *upload_data,
                         size_t *upload_data_size,
                         void **ptr)
{
  char *page;
  struct MHD_Response *response;
  struct Request *request = *ptr;
  int ret = MHD_NO;

  if (request == NULL)
  {
    request = construct_request();
    *ptr = request;

    MHD_get_connection_values(connection, MHD_HEADER_KIND, print_out_key, NULL);

    request->url = construct_url(url);

    if (strcmp(method, MHD_HTTP_METHOD_POST) == 0)
    {
      request->ptr = construct_auth();
      request->pp = MHD_create_post_processor(connection, 256, &auth_iterator, request->ptr);
    }

    printf("headers passed\n");

    return MHD_YES;
  }
  else if (strcmp(method, MHD_HTTP_METHOD_GET) == 0)
  {
    printf("Answer to url <%s>\n", url);

    if (request->url->ext && strcmp(request->url->ext, "es") == 0)
    {
      printf("answer js\n");
      ret = answer_js(connection, request->url);
    }
    else if (strcmp(url, "/auth") == 0)
    {
      // for testing
      init_auth();
    }
    else if (1)
    {
      printf("answer static\n");
      ret = answer_static(connection, request->url);
    }
    else if (strcmp(url, "/") == 0)
    {
      struct Session *session = construct_session(connection);

      page = (char*)malloc(1024);
      snprintf(page,
               1024,
               "<html><body>"
               "<p>URL: %s</p>"
               "<p>Method: %s</p>"
               "<p>Version: %s</p>"
               "<p>Upload data size %lu</p>"
               "<p>Cookie: %s</p>"
               "<form action=\"\" method=\"post\"><div>"
               "<label>user</label><input type=\"text\" name=\"user\"><br>"
               "<label>password</label><input type=\"password\" name=\"password\"><br>"
               "<button type=\"submit\">login</button>"
               "</div></form>"
               "</body></html>",
               url,
               method,
               version,
               *upload_data_size,
               session->cookie);

      response = MHD_create_response_from_buffer(strlen(page),
                                                 (void*)page,
                                                 MHD_RESPMEM_MUST_FREE);

      ret = destruct_session(session, response);

      ret &= MHD_queue_response(connection, MHD_HTTP_OK, response);

      MHD_destroy_response(response);
    }
    else
    {
      ret = answer_404(connection, url);
    }
  }
  else if (strcmp(method, MHD_HTTP_METHOD_POST) == 0)
  {
    if (*upload_data_size)
    {
      ret = MHD_post_process(request->pp, upload_data, *upload_data_size);
      *upload_data_size = 0;
    }
    else
    {
      struct Auth *auth = request->ptr;
      printf("answer to POST for %s role %d\n",
             auth->user,
             auth->roles);
      ret = answer_404(connection, url);
    }
  }

  if (ret == MHD_NO)
  {
    ret = answer_500(connection);
  }

  return ret;
}
