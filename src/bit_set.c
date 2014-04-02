#include <stdio.h>
#include <bit_set.h>

void
fill_bit_set_pos(code_t * src_bit_set)
/* Fill array of code_t with 2^i LSB values, where i is array index. */
/* Assume that size of array is more than MAX_BIT_SET_SIZE. */
/* Example:
   1000000000...
   0100000000...
   0010000000... etc. */
{
  int i;
  int size = sizeof(code_t);
  code_t val = 1 << (size*8 - 1);

  for (i = 0; i < MAX_BIT_SET_SIZE; ++i)
    {
      src_bit_set[i] = val;
      val >>= 1;
    }
}

void
print_bits(code_t bits)
/* print contents of code_t element */
{
  int i;
  int size = sizeof(code_t);
  code_t max_pow = 1 << (size*8 - 1);

  for (i = 0; i < size*8; ++i)
    {
      printf("%u", bits & max_pow ? 1 : 0); /* print last bit and shift left. */
      bits <<= 1;
    }
}

void
print_bit_set(code_t * bit_set)
/* Assume that size of array is more than MAX_BIT_SET_SIZE */
{
  int i;

  puts("=== BITSET ===");

  for (i = 0; i < MAX_BIT_SET_SIZE; ++i)
    {
      print_bits(bit_set[i]);
      printf("\n");
    }

  puts("==============");

}
