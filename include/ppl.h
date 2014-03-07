#include <stdio.h>
#include <ppl_t.h>

#ifndef _HF_FREQ_
#define _HF_FREQ_

#define MAX_PPL_SIZE 256

extern void
calculate_ppl(char *, ppl_t *, int);

extern void
print_ppl(ppl_t *);

#endif
