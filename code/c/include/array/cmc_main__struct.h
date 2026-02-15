#ifndef _cmc_main__struct_h
#define _cmc_main__struct_h

struct cmc_main_state;
struct cmc_main_type;

struct cmc_main
{
  const struct cmc_main_type * type;
  struct cmc_main_state * state;
};

#endif /* _cmc_main__struct_h */
