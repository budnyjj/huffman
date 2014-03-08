#include <stdio.h>
#include <code_t.h>

#ifndef _BIT_SET_
#define _BIT_SET_

#define MAX_BIT_SET_SIZE 32

extern void 
fill_bit_set_pos(code_t *);

extern void 
fill_bit_set_triangle(code_t *);

extern void
print_bits(code_t);

extern void 
print_bit_set(code_t *);

#endif
