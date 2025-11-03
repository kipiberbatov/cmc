#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "diffusion_transient_discrete_primal_strong.h"
#include "diffusion_transient_discrete_primal_strong_solve_trapezoidal_next.h"
#include "mesh.h"

/*
$potential$ stores the final solution $y_0, ..., y_{number_of_steps}$.
$y_0$ is the initial condition.
For $i = 0, ..., number_of_steps$:
  $rhs_final$ is updated using $y_i$ and used to find $y_{i + 1}$.
*/
static void loop(
  double * potential,
  double * rhs_final,
  const struct diffusion_transient_discrete_primal_strong_trapezoidal_loop_data
    * input,
  int number_of_steps)
{
  int i, n;

  n = input->rhs->rows;
  for (i = 0; i < number_of_steps; ++i)
  {
    diffusion_transient_discrete_primal_strong_solve_trapezoidal_next(
      potential + (i + 1) * n, rhs_final, potential + i * n, input);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "loop: error in iteration %d\n", i);
      return;
    }
  }
}

double * diffusion_transient_discrete_primal_strong_solve_trapezoidal(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_transient_discrete_primal_strong * data,
  double time_step,
  int number_of_steps)
{
  int n;
  double * rhs_final, * potential = NULL;

  struct diffusion_transient_discrete_primal_strong_trapezoidal_loop_data *
  input;

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
    fputs("cannot allocate memory for rhs_final\n", stderr);
    goto input_free;
  }

  /* allocate memory for $potential$ -> $n$ elements filled at each step */
  potential = (double *) malloc(sizeof(double) * (number_of_steps + 1) * n);
  if (errno)
  {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot allocate memory for potential\n", stderr);
    goto rhs_final_free;
  }

  /* the initial $n$ elements of $potential$ are the initial condition */
  memcpy(potential, data->initial, sizeof(double) * n);

  /* The following $number_of_steps$ elements of $potential$ (each of size $n$)
   * are calculated iteratively with $rhs_final$ updating at each step.
   */
  loop(potential, rhs_final, input, number_of_steps);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("error in loop calculating final potential\n", stderr);
    free(potential);
    potential =  NULL;
    goto rhs_final_free;
  }

rhs_final_free:
  free(rhs_final);
input_free:
  diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_free(input);
end:
  return potential;
}
