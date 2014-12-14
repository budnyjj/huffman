/**
   @file bit_set.c
   @brief Bit set utilities
   @author Roman Budny
*/

#include <stdio.h>
#include <bit_set.h>

/**
   @brief Fill bit set diagonal with ones"
   @param dest_bit_set Bit set
 */
void
fill_bit_set_pos(code_t * dest_bit_set)
{
  int i;
  int size = sizeof(code_t);
  code_t val = 1 << (size*8 - 1);

  for (i = 0; i < MAX_BIT_SET_SIZE; ++i)
    {
      dest_bit_set[i] = val;
      val >>= 1;
    }
}

/**
   @brief Print bit values of code_t data type
   @param bits Source bits
 */
void
print_bits(code_t bits)
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

/**
   @brief Print set of bit values

   Print set of bit values of code_t data type.
   Assume that size of array is more than MAX_BIT_SET_SIZE.

   @param bit_set Source set of bits
 */
void
print_bit_set(code_t * bit_set)
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
