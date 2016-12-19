#include "myway.h"

int main(int argc, char *argv[])
{
  struct MHD_Daemon *daemon;
  time_t t;

  srand(time(&t));

  daemon = MHD_start_daemon(MHD_USE_DEBUG | MHD_USE_SELECT_INTERNALLY,
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
