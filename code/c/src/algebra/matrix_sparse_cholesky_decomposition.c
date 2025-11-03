// #include <math.h>
// #include <stdlib.h>

// #include "cmc_error_message.h"
// #include "matrix_sparse.h"

// static void matrix_sparse_cholesky_decomposition_set_cols_total(
//   int * l_cols_total, const matrix_sparse * a)
// {
//   int l_columns_j, i, i_local, j, n;
//   int * a_cols_total, * a_row_indices;

//   n = a->rows;
//   a_cols_total = a->cols_total;
//   a_row_indices = a->row_indices;

//   l_cols_total[0] = 0;
//   for (j = 0; j < n; ++j)
//   {
//     l_columns_j = 1;
//     for (i_local = a_cols_total[j]; i_local < a_cols_total[j + 1]; ++i_local)
//     {
//       i = a_row_indices[i_local];
//       if (i > j)
//         ++l_columns_j;
//     }
//     l_cols_total[j + 1] = l_cols_total[j] + l_columns_j;
//   }
// }

// static void matrix_sparse_cholesky_decomposition_set_row_indices(
//   int * l_row_indices, const matrix_sparse * a)
// {
//   int i, i_local, index, j, n;
//   int * a_cols_total, * a_row_indices;

//   n = a->rows;
//   a_cols_total = a->cols_total;
//   a_row_indices = a->row_indices;

//   index = 0;
//   for (j = 0; j < n; ++j)
//   {
//     l_row_indices[index] = j;
//     ++index;
//     for (i_local = a_cols_total[j]; i_local < a_cols_total[j + 1]; ++i_local)
//     {
//       i = a_row_indices[i_local];
//       if (i > j)
//       {
//         l_row_indices[index] = i;
//         ++index;
//       }
//     }
//   }
// }

// static void matrix_sparse_cholesky_decomposition_set_values(
//   double * l_values,
//   const int * l_cols_total,
//   const int * l_row_indices,
//   const matrix_sparse * a)
// {
//   int i, i_local, i_local1, index, j, j_local, k, k_local, n;
//   int * a_cols_total, * a_row_indices;
//   double l_ik, l_jj, l_jk, x;
//   double * a_values;

//   n = a->rows;
//   a_cols_total = a->cols_total;
//   a_row_indices = a->row_indices;
//   a_values = a->values;

//   x = 0;
//   index = 0;
//   for (j = 0; j < n; ++j)
//   {
//     /* diagonal calculation */
//     for (k_local = a_cols_total[j]; k_local < a_cols_total[j + 1]; ++k_local)
//     {
//       k = a_row_indices[k_local];
//       if (k == j)
//       {
//         x = a_values[k_local];
//         break;
//       }
//     }
//     for (k_local = a_cols_total[j]; k_local < a_cols_total[j + 1]; ++k_local)
//     {
//       k = a_row_indices[k_local];
//       if (k < j)
//       {
//         for (j_local = l_cols_total[k]; j_local < l_cols_total[k + 1];
//              ++j_local)
//         {
//           if (l_row_indices[j_local] == j)
//           {
//             l_jk = l_values[j_local];
//             x -= l_jk * l_jk;
//             break;
//           }
//         }
//       }
//     }
//     l_jj = sqrt(x); /* denominator for off-diagonal elements */
//     l_values[index] = l_jj;
//     ++index;
//     for (i_local = a_cols_total[j]; i_local < a_cols_total[j + 1]; ++i_local)
//     {
//       i = a_row_indices[i_local];
//       if (i > j)
//       {
//         /* off-diagonal calculation */
//         for (k_local = a_cols_total[j]; k_local <= a_cols_total[j + 1];
//              ++k_local)
//         {
//           if (a_row_indices[k_local] == i)
//           {
//             x = a_values[k_local];
//             break;
//           }
//         }
//         for (k_local = a_cols_total[j]; k_local <= a_cols_total[j+1]; ++k_local)
//         {
//           k = a_row_indices[k_local];
//           if (k < j)
//           {
//             for (j_local = l_cols_total[k]; j_local < l_cols_total[k + 1];
//                  ++j_local)
//             {
//               if (l_row_indices[j_local] == j)
//               {
//                 for (i_local1 = l_cols_total[k]; i_local1 < l_cols_total[k + 1];
//                     ++i_local1)
//                 {
//                   if (l_row_indices[i_local1] == i)
//                   {
//                     l_ik = l_values[i_local1];
//                     l_jk = l_values[j_local];
//                     x -= l_ik * l_jk;
//                     break;
//                   }
//                 }
//               }
//             }
//           }
//         }
//         l_values[index] = x / l_jj;
//         ++index;
//       }
//     }
//   }
// }

// matrix_sparse * matrix_sparse_cholesky_decomposition(const matrix_sparse * a)
// {
//   int l_nonzero_max, n;
//   matrix_sparse * l;

//   n = a->rows;

//   l = (matrix_sparse *) malloc(sizeof(matrix_sparse));
//   if (l == NULL)
//   {
//     cmc_error_message_position_in_code(__FILE__, __LINE__);
//     cmc_error_message_malloc(sizeof(matrix_sparse), "l");
//     goto end;
//   }

//   l->rows = n;
//   l->cols = n;

//   l->cols_total = (int *) malloc(sizeof(int) * (n + 1));
//   if (l->cols_total == NULL)
//   {
//     cmc_error_message_position_in_code(__FILE__, __LINE__);
//     cmc_error_message_malloc(sizeof(int) * (n + 1), "l_cols_total");
//     goto l_free;
//   }
//   matrix_sparse_cholesky_decomposition_set_cols_total(l->cols_total, a);

//   l_nonzero_max = l->cols_total[n]; /* = (a_nonzero_max + n) / 2 */

//   l->row_indices = (int *) malloc(sizeof(int) * l_nonzero_max);
//   if (l->row_indices == NULL)
//   {
//     cmc_error_message_position_in_code(__FILE__, __LINE__);
//     cmc_error_message_malloc(sizeof(int) * l_nonzero_max, "l_row_indices");
//     goto l_cols_total_free;
//   }
//   matrix_sparse_cholesky_decomposition_set_row_indices(l->row_indices, a);

//   l->values = (double *) malloc(sizeof(double) * l_nonzero_max);
//   if (l->values == NULL)
//   {
//     cmc_error_message_position_in_code(__FILE__, __LINE__);
//     cmc_error_message_malloc(sizeof(double) * l_nonzero_max, "l_values");
//     goto l_row_indices_free;
//   }
//   matrix_sparse_cholesky_decomposition_set_values(l->values,
//     l->cols_total, l->row_indices, a);

//   return l;

//   /* cleaning if an error occurs */
// l_row_indices_free:
//   free(l->row_indices);
// l_cols_total_free:
//   free(l->cols_total);
// l_free:
//   free(l);
// end:
//   return NULL;
// }


#include <stdlib.h>

#include "cmc_error_message.h"
#include "matrix_sparse_private.h"

matrix_sparse * matrix_sparse_cholesky_decomposition(const matrix_sparse * a)
{
  cs a0;
  cs * l0;
  css * S;
  csn * N;
  matrix_sparse * l;

  l = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (l == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(matrix_sparse), "l");
    goto end;
  }

  matrix_sparse_to_cs(&a0, a);

  /* ordering and symbolic analysis */
  S = cs_schol(1, &a0);
  if (S == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot do symbolic analysis of Cholesky decomposition\n", stderr);
    goto end;
  }

  N = cs_chol(&a0, S);
  if (N == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate Cholesky decomposition in csn structure\n", stderr);
    goto S_free;
  }

  l0 = N->L;
  matrix_sparse_from_cs(l, l0);

  free(N);
S_free:
  cs_sfree(S);
end:
  return l;
}
