/**
 * @file main.c
 * Contains the main entry point of the program
 */
#include "lmwd.h"

/** Main program calling functions in lmwd.c.
 *
 * Tasks:
 *  - init random generator
 *  - parse arguments to Config struct
 *  - greet the user, print program info
 *  - start daemon
 *  - wait for input to terminate
 *  - stop daemon
 *
 * @param argc number of command line arguments
 * @param argv array of command line arguments
 * @return 0 on success, 1 on bad configuration, 2 when the service could
 * not start.
 */
int main(int argc, char *argv[])
{
  struct Config *config = NULL;
  struct MHD_Daemon *daemon = NULL;
  int ret = 0;

  init_random();

  config = parse_config(argc, argv);

  if (config != NULL
      && config->run_mode == RUN_CONSOLE)
  {
    print_info(argv[0], config);
    daemon = start_service(config);

    if (daemon != NULL)
    {
      (void)getchar();
    }
    else
    {
      printf("Could not start daemon\n");
      ret = 2;
    }
  }
  else if (config != NULL
           && config->run_mode != RUN_NO_OP)
  {
    // Bad configuration
    ret = 1;
  }

  stop_service(daemon, config);

  return ret;
}
