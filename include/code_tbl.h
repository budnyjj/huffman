#include <stdio.h>
#include <bit_set.h>

#ifndef _CODE_TABLE_
#define _CODE_TABLE_

#define MAX_CODE_TBL_SIZE 256
#define CODE_NOT_EXISTS -1

struct hf_code {
  int size; /* size of significal part */
  code_t code;
};

extern void
init_code_tbl(struct hf_code *);

extern void
print_code(int, struct hf_code);

extern void 
print_code_tbl(struct hf_code *);

#endif
