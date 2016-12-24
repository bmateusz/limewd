#include "session.h"

const char *check_or_create_session(struct MHD_Connection *connection,
                                    char **created)
{
  const char *cookie;
  cookie = MHD_lookup_connection_value(connection,
                                       MHD_COOKIE_KIND,
                                       "session");
  if (cookie == NULL)
  {
    char *new_session_id = (char*)malloc(64);
    snprintf(new_session_id,
             sizeof(char) * 64,
             "%X%X%X%X",
             (unsigned int)rand(),
             (unsigned int)rand(),
             (unsigned int)rand(),
             (unsigned int)rand());

    cookie = new_session_id;
    *created = new_session_id;
    printf("new session: <%s>\n", cookie);
  }
  return cookie;
}

int set_session(char *session,
                struct MHD_Response *response)
{
  char set_session_id[64];
  snprintf(set_session_id,
           sizeof(set_session_id),
           "session=%s",
           session);
  free(session);

  printf("set cookie: %s", set_session_id);
  return MHD_add_response_header(response,
                                 MHD_HTTP_HEADER_SET_COOKIE,
                                 set_session_id);
}
