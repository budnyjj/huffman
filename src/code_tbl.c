/**
   @file code_tbl.c
   @brief Code table utilities
   @author Roman Budny
*/

#include <stdio.h>
#include <code_tbl.h>
#include <p_utils.h>

/* Print huffman code properties assigned to character */
static void 
print_code(int character, struct hf_code code)
{
  printf("%c: %4d: ", character, code.size);
  print_bits(code.code);
  printf("\n");
}

/**
   @brief Print content of code table
   @param tbl Code table
 */
void 
print_code_tbl(const struct hf_code *const tbl)
{
  int i;

  CHKPTR(tbl);
  
  puts("=== TABLE OF ASSIGNED HUFFMAN CODES ===");

  for (i = 0; i < MAX_CODE_TBL_SIZE; ++i)
      print_code(i, tbl[i]);

  puts("=======================================");
}
