#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "forman_coordinates_private.h"

void forman_coordinates(
  double * m_forman_coordinates, const mesh * m, const char * format)
{
  if (!strcmp(format, "--standard"))
    forman_coordinates_standard(m_forman_coordinates, m);
  else if (!strcmp(format, "--polar"))
    forman_coordinates_disk_polar(m_forman_coordinates, m);
  else if (!strcmp(format, "--centroid"))
    forman_coordinates_centroid(m_forman_coordinates, m);
  else
  {
    errno = EINVAL;
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
  }
}
