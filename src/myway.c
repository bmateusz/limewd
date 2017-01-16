#include "myway.h"

void print_info(const char *executable, struct Config *config)
{
  printf("start %s\n"
         "libmicrohttpd version: v%s\n"
         "duktape version: %s\n"
         "sqlite version: v%s\n",
         executable,
         MHD_get_version(),
         DUK_GIT_DESCRIBE,
         SQLITE_VERSION);

  if (config)
  {
    printf("\n"
           "Port: %d\n",
           config->port);
  }
}

void init_random()
{
  time_t t;
  srand(time(&t));
}

struct Config *parse_config(int argc, char *argv[])
{
  struct Config *config = malloc(sizeof(struct Config));
  int i;

  config->port = 8888; /* default port */

  for (i = 1; i < argc; ++i)
  {
    if (strcmp("-p", argv[i]) == 0 && ++i < argc)
    {
      sscanf(argv[i], "%hu", &(config->port));
    }
  }
  return config;
}

struct MHD_Daemon *start_service(struct Config *config)
{
  if (config == NULL) return NULL;
  return MHD_start_daemon(MHD_USE_DEBUG | MHD_USE_EPOLL_INTERNALLY,
                          config->port,
                          &on_client_connect, NULL,
                          &answer_to_connection, NULL,
                          MHD_OPTION_CONNECTION_TIMEOUT, 15,
                          MHD_OPTION_NOTIFY_COMPLETED, &request_completed, NULL,
                          MHD_OPTION_END);
}

void stop_service(struct MHD_Daemon *daemon, struct Config *config)
{
  MHD_stop_daemon(daemon);
  free(config);
}
