#include "connect.h"

static void get_ip_str(const struct sockaddr *sa,
                       char *s,
                       unsigned int maxlen)
{
  switch(sa->sa_family) {
    case AF_INET:
      inet_ntop(AF_INET, &(((const struct sockaddr_in *)sa)->sin_addr),
          s, maxlen);
      break;

    case AF_INET6:
      inet_ntop(AF_INET6, &(((const struct sockaddr_in6 *)sa)->sin6_addr),
          s, maxlen);
      break;

    default:
      strncpy(s, "Unknown AF", maxlen);
  }
}

int on_client_connect(void *cls UNUSED,
                      const struct sockaddr *addr,
                      socklen_t addrlen)
{
  char str[addrlen];
  get_ip_str(addr, str, addrlen);
  printf("connected %s\n", str);
  return MHD_YES;
}

void request_completed(void *cls UNUSED,
                       struct MHD_Connection *connection UNUSED,
                       void **ptr,
                       enum MHD_RequestTerminationCode toe)
{
  struct Request *request = *ptr;

  printf("request completed %d\n", toe);

  destruct_request(request);
}
