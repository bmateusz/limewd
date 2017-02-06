#include "lmwd.h"

void print_info(const char *executable, struct Config *config)
{
  printf("limewd\n"
         "libmicrohttpd version: v%s\n"
         "duktape version: %s\n"
         "sqlite version: v%s\n",
         MHD_get_version(),
         DUK_GIT_DESCRIBE,
         SQLITE_VERSION);

  if (config)
  {
    printf("start %s\n"
           "port: %d\n",
           executable,
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
  int error = 0;

  config->port = 8888; /* default port */
  config->timeout = 15; /* default timeout */
  config->run_mode = RUN_CONSOLE;

  for (i = 1; i < argc && !error; ++i)
  {
    if (strcmp("-p", argv[i]) == 0 && i + 1 < argc)
    {
      ++i;
      error = sscanf(argv[i], "%hu", &(config->port));
      if (error < 1
          || config->port < 1
          || config->port >= 65535)
      {
        error = -1;
        printf("Port has to be a number between 1 and 65535\n");
      }
    }
    else if (strcmp("-t", argv[i]) == 0 && i + 1 < argc)
    {
      ++i;
      error = sscanf(argv[i], "%u", &(config->timeout));
      if (error < 1
          || config->timeout >= 65535)
      {
        error = -1;
        printf("Invalid timeout value\n");
      }
    }
    else if (strcmp("-v", argv[i]) == 0)
    {
      print_info(argv[0], NULL);
      config->run_mode = RUN_NO_OP;
    }
    else
    {
      printf("usage:\n  %s [-p port] [-t timeout] [-v]\n", argv[0]);
      error = -1;
    }
  }

  if (error >= 0)
  {
    return config;
  }
  else
  {
    free(config);
    return NULL;
  }
}

struct MHD_Daemon *start_service(struct Config *config)
{
  if (config != NULL)
  {
    return MHD_start_daemon(MHD_USE_DEBUG | MHD_USE_EPOLL_INTERNALLY,
                            config->port,
                            &on_client_connect, NULL,
                            &answer_to_connection, NULL,
                            MHD_OPTION_CONNECTION_TIMEOUT, config->timeout,
                            MHD_OPTION_NOTIFY_COMPLETED, &request_completed, NULL,
                            MHD_OPTION_END);
  }
  else
  {
    return NULL;
  }
}

void stop_service(struct MHD_Daemon *daemon, struct Config *config)
{
  if (daemon != NULL)
  {
    MHD_stop_daemon(daemon);
  }
  free(config);
}
