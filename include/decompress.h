#ifndef _DECOMPRESS_
#define _DECOMPRESS_

#include <verbosity_t.h>

int
decompress(const char *const src_fname,
         const char *const dest_fname,
         verbosity_t verbose);

#endif
