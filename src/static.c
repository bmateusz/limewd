#include "static.h"

int answer_static(struct MHD_Connection *connection,
                  struct Url *url)
{
  struct MHD_Response *response;
  int ret = MHD_NO;
  int fd;
  struct stat sbuf;

  const char *filename = url->path;
  const char *mime = get_mime(url);
  char etag[32];
  const char *if_none_match;

  if ((fd = open(filename, O_RDONLY)) > 0
      && fstat(fd, &sbuf) == 0
      && strstr(filename, "..") == NULL)
  {
    printf("Answer %s [%s]\n", filename, mime);

    snprintf(etag, 32, "\"%ld\"", sbuf.st_mtime);
    if_none_match = MHD_lookup_connection_value(connection, MHD_HEADER_KIND, MHD_HTTP_HEADER_IF_NONE_MATCH);

    printf("Check <%s> vs <%s>\n", etag, if_none_match);
    if (if_none_match != NULL
        && strcmp(etag, if_none_match) == 0)
    {
      ret = answer_304(connection);
      close(fd);
    }
    else
    {
      response = MHD_create_response_from_fd_at_offset64(sbuf.st_size, fd, 0);

      ret = MHD_add_response_header(response, MHD_HTTP_HEADER_CONTENT_TYPE, mime);
      ret &= MHD_add_response_header(response, MHD_HTTP_HEADER_ETAG, etag);
      ret &= MHD_add_response_header(response, MHD_HTTP_HEADER_CACHE_CONTROL, "max-age=5"); /* 86400 */
      ret &= MHD_queue_response(connection, MHD_HTTP_OK, response);
      MHD_destroy_response(response);
    }
  }
  else
  {
    printf("Could not open %s\n", filename);
    close(fd);
    ret = answer_404(connection, url->url);
  }
  return ret;
}
