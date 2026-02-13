#ifndef _cmc_error_message_h
#define _cmc_error_message_h

#include <stddef.h>

#include "color.h"

void cmc_error_message_position_in_code(const char * file, int line);
void cmc_error_message_string(const char * s);
void cmc_error_message_variable_int(int n);
void cmc_error_message_variable_double(double x);
void cmc_error_message_variable_string(const char * s);
void cmc_error_message_memory_allocate(const char * name);
void cmc_error_message_cannot_calculate(const char * name);
void cmc_error_message_malloc(size_t size, const char * name);
void cmc_error_message_number_of_command_line_arguments_mismatch(
  int ARGC, int argc);

#endif /* _cmc_error_message_h */
