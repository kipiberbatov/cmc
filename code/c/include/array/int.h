#ifndef _int_h
#define _int_h

#include <stdio.h>

/************************************ int *************************************/
int int_file_scan(FILE * in);

int int_string_scan(const char * s);

void int_string_scan_void(void * result, int * status, const char * s);

void int_file_print_void(FILE * out, const void * x);

void int_set_default_void(void * argument, const void * default_argument);

int int_greatest_common_divisor(int m, int n);

int int_power(int a, int n);

int int_factorial(int n);

int int_binomial(int n, int k);

void int_swap(int * a, int * b);

/********************************* int_array **********************************/
int * int_array_file_scan(FILE * in, int n, const char * format);

void int_array_file_print(FILE * out, int n, const int * a, const char * format);

void int_array_assign_identity(int * a, int n);

void int_array_assign_constant(int * a, int n, int c);

void int_array_compress_to_sparse_array(
  int * b, int size, const int * positions, const int * a);

void int_array_assemble_from_sparse_array(
  int * b, int size, const int * positions, const int * a);

void int_array_sum(int * c, int n, const int * a, const int * b);

void int_array_set_difference(
  int * b_bar, int p, const int * a, int q, const int * b);

int int_array_total_sum(int n, const int * a);

int int_array_total_product(int n, const int * a);

int int_array_member_index(int n, const int * a, int element);

int int_array_member(int n, const int * a, int element);

int int_array_flatten_index(int d, const int * dimensions, const int * indices);

int int_array_positive(int n, const int * a);

void int_array_cartesian_product_next(int * a, int d, const int * n);

void int_array_combination_next(int * a, int m, int n);

int int_array_combination_index(int * comb, int m, int n);

/********************************* int_array2 *********************************/
void int_array2_free(int ** arr, int a0);

#endif /* _int_h */
