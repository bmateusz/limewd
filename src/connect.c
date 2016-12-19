#include "connect.h"

void get_ip_str(const struct sockaddr *sa,
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

int on_client_connect(void *cls,
                      const struct sockaddr *addr,
                      socklen_t addrlen)
{
  char str[INET6_ADDRSTRLEN];
  get_ip_str(addr, str, INET6_ADDRSTRLEN);
  printf("connected %s\n", str);
  return MHD_YES;
}

void request_completed(void *cls,
                       struct MHD_Connection *connection,
                       void **con_cls,
                       enum MHD_RequestTerminationCode toe)
{
  printf("request completed\n");
}
