#include <stdio.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "mesh_measures.h"
#include "mesh_qc.h"

void mesh_measures_simplicial_or_quasi_cubical(
  double *** m_measures, int * status, const struct mesh * m)
{
  int d, p;
  int * m_cn;
  double ** vol;

  d = m->dim;
  m_cn = m->cn;
  *m_measures = (double **) malloc(sizeof(double *) * (d + 1));
  if (*m_measures == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double *) * (d + 1), "*m_measures");
    *status = 1;
    return;
  }
  vol = *m_measures;

  for (p = 0; p <= d; ++p)
  {
    vol[p] = (double *) malloc(sizeof(double) * m_cn[p]);
    if (vol[p] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot allocate %s%zu%s bytes of memory for %s%s[%d]%s\n",
         color_variable, sizeof(double) * m_cn[p], color_none,
         color_variable, "vol", p, color_none);
      *status = 1;
      return;
    }
  }

  for (p = 0; p <= d; ++p)
    mesh_measure_single(vol[p], m, p);
}
