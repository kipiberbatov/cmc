#include "array_file_print.h"

/******************************* array_file_print1 ********************************/
static void array_file_print1_local(FILE * out, int a0,
                                int * p1, const int * a1)
{
  int i;
  fputc('{', out);
  for (i = 0; i < a0 - 1; ++i)
  {
    fprintf(out, "%d,", a1[*p1]);
    ++*p1;
  }
  if (a0 > 0)
  {
    fprintf(out, "%d", a1[*p1]);
    ++*p1;
  }
  fputc('}', out);
}

void array_file_print1(FILE * out, int a0, const int * a1)
{
  int p1 = 0;
  array_file_print1_local(out, a0, &p1, a1);
}

/******************************* array_file_print2 ********************************/
static void array_file_print2_local(FILE * out, int a0,
                                int * p1, const int * a1,
                                int * p2, const int * a2)
{
  int i;
  fputc('{', out);
  for (i = 0; i < a0 - 1; ++i)
  {
    array_file_print1_local(out, a1[*p1], p2, a2);
    fputc(',', out);
    ++*p1;
  }
  if (a0 > 0)
  {
    array_file_print1_local(out, a1[*p1], p2, a2);
    ++*p1;
  }
  fputc('}', out);
}

void array_file_print2(FILE * out, int a0, const int * a1, const int * a2)
{
  int p1 = 0, p2 = 0;
  array_file_print2_local(out, a0, &p1, a1, &p2, a2);
}

/******************************* array_file_print3 ********************************/
static void array_file_print3_local(FILE * out, int a0,
                                int * p1, const int * a1,
                                int * p2, const int * a2,
                                int * p3, const int * a3)
{
  int i;
  fputc('{', out);
  for (i = 0; i < a0 - 1; ++i)
  {
    array_file_print2_local(out, a1[*p1], p2, a2, p3, a3);
    fputc(',', out);
    ++*p1;
  }
  if (a0 > 0)
  {
    array_file_print2_local(out, a1[*p1], p2, a2, p3, a3);
    ++*p1;
  }
  fputc('}', out);
}

void array_file_print3(FILE * out, int a0, const int * a1, const int * a2,
                   const int * a3)
{
  int p1 = 0, p2 = 0, p3 = 0;
  array_file_print3_local(out, a0, &p1, a1, &p2, a2, &p3, a3);
}

/******************************* array_file_print4 ********************************/
static void array_file_print4_local(FILE * out, int a0,
                                int * p1, const int * a1,
                                int * p2, const int * a2,
                                int * p3, const int * a3,
                                int * p4, const int * a4)
{
  int i;
  fputc('{', out);
  for (i = 0; i < a0 - 1; ++i)
  {
    array_file_print3_local(out, a1[*p1], p2, a2, p3, a3, p4, a4);
    fputc(',', out);
    ++*p1;
  }
  if (a0 > 0)
  {
    array_file_print3_local(out, a1[*p1], p2, a2, p3, a3, p4, a4);
    ++*p1;
  }
  fputc('}', out);
}

void array_file_print4(FILE * out, int a0, const int * a1, const int * a2,
                   const int * a3, const int * a4)
{
  int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
  array_file_print4_local(out, a0, &p1, a1, &p2, a2, &p3, a3, &p4, a4);
}
