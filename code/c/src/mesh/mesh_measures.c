#include <stdio.h>
#include <string.h>

#include "cmc_error_message.h"
#include "mesh_measures.h"

struct mesh;

void mesh_measures(double *** m_measures, int * status,
  const struct mesh * m, const char * method)
{
  void (*measurer)(double *** m_measures, int * status, const struct mesh * m);

  if (!strcmp(method, "default"))
    measurer = mesh_measures_default;
  else if (!strcmp(method, "simplicial-or-quasi-cubical"))
    measurer = mesh_measures_simplicial_or_quasi_cubical;
  else if (!strcmp(method, "polar-forman"))
    measurer = mesh_measures_disk_polar_forman;
  else if (!strcmp(method, "hemisphere-forman"))
    measurer = mesh_measures_hemisphere_polar_forman;
  else
    measurer = NULL;

  if (measurer == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "method %s is not supported\n", method);
    *status = 1;
    return;
  }

  measurer(m_measures, status, m);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate m_measures using method %s\n", method);
  }
}
