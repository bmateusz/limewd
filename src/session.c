#include "session.h"

struct Session *construct_session(struct MHD_Connection *connection)
{
  struct Session *session = malloc(sizeof(struct Session));
  session->cookie = MHD_lookup_connection_value(connection,
                                                MHD_COOKIE_KIND,
                                                "session");
  if (session->cookie == NULL)
  {
    char *new_session_id = (char*)malloc(64);
    snprintf(new_session_id,
             sizeof(char) * 64,
             "%X%X%X%X",
             (unsigned int)rand(),
             (unsigned int)rand(),
             (unsigned int)rand(),
             (unsigned int)rand());

    session->cookie = new_session_id;
    session->created = new_session_id;
    printf("new session: <%s>\n", session->cookie);
  }
  else
  {
    session->created = NULL;
  }
  return session;
}

int destruct_session(struct Session *session,
                     struct MHD_Response *response)
{
  char set_session_id[64];
  int ret = MHD_YES;

  if (session->created != NULL)
  {
    snprintf(set_session_id,
             sizeof(set_session_id),
             "session=%s",
             session->created);

    ret = MHD_add_response_header(response,
                                  MHD_HTTP_HEADER_SET_COOKIE,
                                  set_session_id);
    printf("set cookie: %s", set_session_id);
    free(session->created);
  }

  free(session);
  return ret;
}
