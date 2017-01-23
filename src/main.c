/**
 * @file main.c
 * Contains the main entry point of the program
 */
#include "myway.h"

/** Main program calling functions in myway.c.
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
 * @return 0 on success
 */
int main(int argc, char *argv[])
{
  struct Config *config;
  struct MHD_Daemon *daemon;
  int ret = 0;

  init_random();

  config = parse_config(argc, argv);

  print_info(argv[0], config);

  daemon = start_service(config);

  if (daemon == NULL)
  {
    printf("Could not start daemon\n");
    ret = 1;
  }
  else
  {
    (void)getchar();
  }

  stop_service(daemon, config);

  return ret;
}
