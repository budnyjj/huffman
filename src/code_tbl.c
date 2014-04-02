#include <stdio.h>
#include <code_tbl.h>
#include <p_utils.h>

static void 
print_code(int character, struct hf_code code)
/* Print huffman code properties assigned to character */
{
  printf("%c: %4d: ", character, code.size);
  print_bits(code.code);
  printf("\n");
}

void 
print_code_tbl(const struct hf_code *const tbl)
/* Print content of code table */
{
  int i;

  CHKPTR(tbl);
  
  puts("=== TABLE OF ASSIGNED HUFFMAN CODES ===");

  for (i = 0; i < MAX_CODE_TBL_SIZE; ++i)
      print_code(i, tbl[i]);

  puts("=====================================");
}
