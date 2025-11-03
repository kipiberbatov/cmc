#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "diffusion_transient_discrete_primal_strong.h"
#include "diffusion_transient_discrete_primal_strong_solve_trapezoidal_next.h"
#include "double_array.h"
#include "double_array_sequence_dynamic.h"
#include "mesh.h"

/*
$potential$ stores the final solution $y_0, ..., y_{number_of_steps}$.
$y_0$ is the initial condition.
Until error is less than $tolerance$:
  $rhs_final$ is updated using $y_i$ and used to find $y_{i + 1}$.
*/
static void loop(
  struct double_array_sequence_dynamic * potential,
  double * rhs_final,
  const struct diffusion_transient_discrete_primal_strong_trapezoidal_loop_data
    * input,
  double tolerance)
{
  int i, n;
  double relative_norm;

  i = 0;
  n = input->rhs->rows;

  do
  {
    if (i == potential->capacity - 1)
    {
      double_array_sequence_dynamic_resize(potential);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "loop: cannot resize in iteration %d\n", i);
        return;
      }
    }

    potential->values[i + 1] = (double *) malloc(sizeof(double) * n);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "loop: cannot allocate %s%ld%s bytes of memory for "
        "potential->values[%s%d%s]\n",
        color_variable, sizeof(double) * n, color_none,
        color_variable, i + 1, color_none);
      return;
    }

    diffusion_transient_discrete_primal_strong_solve_trapezoidal_next(
      potential->values[i + 1], rhs_final, potential->values[i], input);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "loop: cannot calculate potential->values[%d]\n", i + 1);
      return;
    }

    relative_norm = double_array_pair_norm_uniform_relative(
      n, potential->values[i], potential->values[i + 1]);
    ++potential->length;
    ++i;
  }
  while (relative_norm >= tolerance);
}

struct double_array_sequence_dynamic *
diffusion_transient_discrete_primal_strong_solve_trapezoidal_to_steady_state(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_transient_discrete_primal_strong * data,
  double time_step,
  double tolerance)
{
  int n;
  double * rhs_final;

  struct diffusion_transient_discrete_primal_strong_trapezoidal_loop_data *
  input;

  struct double_array_sequence_dynamic * potential = NULL;

  input =
  diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_initialize(
    m, m_cbd_0, m_cbd_star_1, data, time_step);
  if (input == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot initialize loop input\n", stderr);
    goto end;
  }

  n = m->cn[0];

  /* allocate memory for $rhs_final$ -> uppdated at each step of the loop */
  rhs_final = (double *) malloc(sizeof(double) * n);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * n, "rhs_final");
    goto input_free;
  }

  potential = double_array_sequence_dynamic_initialize(n);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot initialize potential with size %d\n", n);
    goto rhs_final_free;
  }

  /* the initial $potential->values[0]$ is the initial condition */
  memcpy(potential->values[0], data->initial, sizeof(double) * n);

  /* The following elements of $potential$ (each of size $n$)
   * are calculated iteratively with $rhs_final$ updating at each step
   * (until error is less than tolerance).
   */
  loop(potential, rhs_final, input, tolerance);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("error in loop calculating final potential\n", stderr);
    double_array_sequence_dynamic_free(potential);
    potential = NULL;
    goto rhs_final_free;
  }

rhs_final_free:
  free(rhs_final);
input_free:
  diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_free(input);
end:
  return potential;
}
