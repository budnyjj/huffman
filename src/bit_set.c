#include <bit_set.h>

void 
fill_bit_set(code_t * src_bit_set)
/* Fill array of code_t with 2^i values, where i is array index. */
/* Assume that size of array is more than MAX_BIT_SET_SIZE */
{
  int i;
  code_t val = 1 << (sizeof(code_t)*8 - 1);

  for (i = 0; i < MAX_BIT_SET_SIZE; ++i)
    {
      src_bit_set[i] = val;
      val >>= 1;
    }
}

void 
print_bit_set(code_t * bit_set)
/* Fill array of code_t with
   (0 repeated i times...1, 0 remaining)
   values, where i is array index. */
/* Assume that size of array is more than MAX_BIT_SET_SIZE */
{
  int i;
  int size = sizeof(code_t);
  code_t max_pow = 1 << (size*8 - 1);

  puts("=== BITSET ===");

  for (i = 0; i < MAX_BIT_SET_SIZE; ++i)
    {
      int j;
      code_t num = bit_set[i];
      for(j = 0; j < size*8; ++j)
	{
	  printf("%u", num & max_pow ? 1 : 0); /* print last bit and shift left. */
	  num <<= 1;
	}
      printf("\n");
    }

  puts("==============");

}
