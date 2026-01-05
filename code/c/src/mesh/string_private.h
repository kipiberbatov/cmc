#ifndef _string_private_h
#define _string_private_h

#include <stdio.h>

/*
Compares the initial $n characters of a string $s with the $n characters
following in a file $in.
Returns 0 if they are the same, 1 (respectively, -1), if at the first one that
they differ in has a higher (respectively, lower), -2 if EOF occurs
*/
int string_compare_with_file(FILE * in, int n, const char * s);

/* like fgets, but does not discriminate against newlines */
void string_file_scan(FILE * in, char * s, int n);

/*
Locate a string `s` occupying a full line in `file`.
Set `status` to 1 if the search is unsucessful.
The string cannot occupy more than 80 symbols.
*/
void string_locate_in_file_line(FILE * file, int * status, const char * s);

#endif /* _string_private_h */
