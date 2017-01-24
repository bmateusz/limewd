/**
 * @file lmwd.h
 * Main header of the library.
 *
 * @mainpage
 * There will be the introduction of limewd,
 * the Lightweight Minimal Ecmascript powered Www Daemon
 */
#ifndef LMWD_H
#define LMWD_H

#include <time.h>

#include "mhd.h"
#include "duktape.h"
#include "sqlite.h"
#include "answer.h"
#include "connect.h"

/** Configuration structure. */
struct Config
{
  /** Port which will be used by the libmicrohttp daemon. */
  uint16_t port;
};

/** Print information at startup.
 * @param executable name of the executable, practically argv[0] from startup parameters
 * @param config the Config structure
 */
void print_info(const char *executable, struct Config *config);

/** Init random generator. */
void init_random();

/** Parse configuration parameters.
 * @param argc number of command line arguments
 * @param argv array of command line arguments
 */
struct Config *parse_config(int argc, char *argv[]);

/** Start libmicrohttp daemon.
 * @param config the Config structure
 */
struct MHD_Daemon *start_service(struct Config *config);

/** Stop libmicrohttp daemon.
 * @param daemon the libmicrohttp daemon
 * @param config the Config structure
 */
void stop_service(struct MHD_Daemon *daemon, struct Config *config);

#endif
