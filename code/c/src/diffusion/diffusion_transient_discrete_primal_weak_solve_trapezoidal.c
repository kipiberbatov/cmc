#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "diffusion_transient_discrete_primal_weak.h"
#include "diffusion_transient_discrete_primal_weak_solve_trapezoidal_next.h"
#include "diffusion_transient_discrete_primal_weak_trapezoidal_loop_data.h"
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
  const struct diffusion_transient_discrete_primal_weak_trapezoidal_loop_data *
    input,
  int number_of_steps)
{
  int i, m_cn_0;

  m_cn_0 = input->rhs->rows;
  for (i = 0; i < number_of_steps; ++i)
  {
    diffusion_transient_discrete_primal_weak_solve_trapezoidal_next(
      potential + m_cn_0 * (i + 1), rhs_final, potential + m_cn_0 * i, input);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate loop iteration %d\n", i);
      return;
    }
  }
}

double * diffusion_transient_discrete_primal_weak_solve_trapezoidal(
  const struct mesh * m,
  const double * m_inner_0,
  const double * m_inner_1,
  const struct diffusion_transient_discrete_primal_weak * data,
  double time_step,
  int number_of_steps)
{
  int m_cn_0;
  double * rhs_final, * potential = NULL;
  struct diffusion_transient_discrete_primal_weak_trapezoidal_loop_data * input;

  input =
  diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_initialize(
    m, m_inner_0, m_inner_1, data, time_step);
  if (input == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot initialize loop input\n", stderr);
    goto end;
  }

  m_cn_0 = m->cn[0];

  /* allocate memory for $rhs_final$ -> uppdated at each step of the loop */
  rhs_final = (double *) malloc(sizeof(double) * m_cn_0);
  if (rhs_final == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_cn_0, "rhs_final");
    goto input_free;
  }

  /* allocate memory for $potential$ -> $n$ elements filled at each step */
  potential = (double*) malloc(sizeof(double) * (number_of_steps + 1) * m_cn_0);
  if (potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * (number_of_steps + 1) * m_cn_0,
      "potential");
    goto rhs_final_free;
  }

  /* the initial $n$ elements of $potential$ are the initial condition */
  memcpy(potential, data->initial, sizeof(double) * m_cn_0);

  /* The following $number_of_steps$ elements of $potential$ (each of size $n$)
   * are calculated iteratively with $rhs_final$ updating at each step.
   */
  loop(potential, rhs_final, input, number_of_steps);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate potential\n", stderr);
    free(potential);
    potential =  NULL;
    goto rhs_final_free;
  }

rhs_final_free:
  free(rhs_final);
input_free:
  diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_free(input);
end:
  return potential;
}
