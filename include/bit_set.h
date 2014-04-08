/**
   @file bit_set.h
   @brief Provides functions for working with arrays of bits
   @author Roman Budny
 */

#ifndef _BIT_SET_
#define _BIT_SET_

#include <code_t.h>

#define MAX_BIT_SET_SIZE 32

/**
   @brief Fill array of bits with positional values
   
   Fill array of code_t with 2^i LSB values, where i is array index.
   Assume that size of array is more than MAX_BIT_SET_SIZE.
   For example:
   1000000000...
   0100000000...
   0010000000... etc.

   @param[out] src_bit_set Destination array
 */
void 
fill_bit_set_pos(code_t * dest_bit_set);

/**
   @brief Print contents of huffman code in binary form
   @param[in] bits Source huffman code
 */
void
print_bits(code_t bits);

/**
   @brief Print contents of array of huffman codes in binary form
   @param[in] bit_set Source array of huffman codes
 */
void 
print_bit_set(code_t * bit_set);

#endif
