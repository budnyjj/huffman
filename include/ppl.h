#ifndef _HF_FREQ_
#define _HF_FREQ_

#include <ppl_t.h>
#include <verbosity_t.h>

#define MAX_PPL_SIZE 256

ppl_t
calculate_ppl(FILE* src, ppl_t *const dest_ppl,
              verbosity_t verbose);

long int
read_ppl(FILE* src, ppl_t *const dest_ppl,
         int num_code, verbosity_t verbose);

int
write_ppl(const ppl_t *const src_ppl, FILE* dest);

int 
char_with_max_ppl(const ppl_t *const src_ppl);

#endif
