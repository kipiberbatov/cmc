#ifndef _simplex_h
#define _simplex_h

#include <stdio.h>

typedef struct simplex
{
  int dim_embedded;
  int dim;
  double * coord;
} simplex;

void simplex_free(simplex * s);

simplex * simplex_file_scan(FILE * in);

void simplex_file_print(FILE * out, const simplex * s, const char * format);

double simplex_measure(const simplex * s);

void simplex_centroid(double * s_medicenter, const simplex * s);

#endif /* _simplex_h */
