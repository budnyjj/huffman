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

void 
print_code_tbl(struct hf_code * tbl)
/* Print content of code table */
{
  int i;
  int size = sizeof(code_t);
  code_t max_pow = 1 << (size*8 - 1);

  puts("=== TABLE OF ASSIGNED HUFFMAN CODES ===");

  for (i = 0; i < MAX_CODE_TBL_SIZE; ++i)
    {
      int j;
      code_t code = tbl[i].code;
      printf("%c:\t%10d: ", i, tbl[i].size);

      for (j = 0; j < size * 8; ++j)
	{
	  printf("%u", code & max_pow ? 1 : 0); /* print last bit and shift left. */
	  code <<= 1;
	}
      printf("\n");
    }

  puts("=====================================");
}
