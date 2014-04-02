#ifndef _CODE_TABLE_
#define _CODE_TABLE_

#include <bit_set.h>

#define MAX_CODE_TBL_SIZE 256
#define CODE_NOT_EXISTS -1

struct hf_code {
  int size; /* size of significant part */
  code_t code;
};

void
init_code_tbl(struct hf_code *const);

void 
print_code_tbl(const struct hf_code *const);

#endif
