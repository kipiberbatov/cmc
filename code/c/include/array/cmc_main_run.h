struct cmc_main_generic_functions;
struct cmc_main_compute_and_print;

void cmc_main_run(
  int * status,
  int argc,
  char ** argv,
  const struct cmc_main_generic_functions * generic,
  const struct cmc_main_compute_and_print * compute_and_print);
