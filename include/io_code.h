#include <stdio.h>

#include <bit_set.h>
#include <code_tbl.h>

#ifndef _IO_CODE_
#define _IO_CODE_

#define CODE_BUFFER_SIZE 1024 /* how to determine optimal size? */

extern void
compress(char *, char *, struct hf_code *, int);

#endif
