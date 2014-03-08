#include <code_tbl.h>

void
init_code_tbl(struct hf_code * tbl)
/* Fill tbl with zero values. */
{
  int i;

  for (i = 0; i < MAX_CODE_TBL_SIZE; ++i)
    {
      tbl[i].code = 0;
      tbl[i].size = CODE_NOT_EXISTS;
    }
}

void print_code(int character, struct hf_code code)
/* Print huffman code properties assigned to character */
{
  printf("%c: %4d: ", character, code.size);
  print_bits(code.code);
  printf("\n");
}

void 
print_code_tbl(struct hf_code * tbl)
/* Print content of code table */
{
  int i;

  puts("=== TABLE OF ASSIGNED HUFFMAN CODES ===");

  for (i = 0; i < MAX_CODE_TBL_SIZE; ++i)
      print_code(i, tbl[i]);

  puts("=====================================");
}
