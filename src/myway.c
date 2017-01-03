#include "myway.h"

int main(int argc, char *argv[])
{
  struct MHD_Daemon *daemon;
  time_t t;

  srand(time(&t));

  printf("start %s\n"
         "libmicrohttpd version: v%s\n"
         "duktape version: %s\n"
         "sqlite version: v%s\n",
         argv[0],
         MHD_get_version(),
         DUK_GIT_DESCRIBE,
         SQLITE_VERSION);

  daemon = MHD_start_daemon(MHD_USE_DEBUG | MHD_USE_EPOLL_INTERNALLY,
                            PORT,
                            &on_client_connect, NULL,
                            &answer_to_connection, NULL,
                            MHD_OPTION_CONNECTION_TIMEOUT, 15,
                            MHD_OPTION_NOTIFY_COMPLETED, &request_completed, NULL,
                            MHD_OPTION_END);
  if (NULL == daemon)
  {
    printf("Could not start daemon");
    return 1;
  }

  (void)getchar();

  MHD_stop_daemon(daemon);
  return 0;
}
