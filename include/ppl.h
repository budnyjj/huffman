/**
   @file ppl.h
   @brief Contains tools for work with array of character popularity

   Character popularity is array of ppl_t elements,
   each of them contains number of character repetitions in source.
   
   @author Roman Budny
 */

#ifndef _HF_FREQ_
#define _HF_FREQ_

#include <ppl_t.h>
#include <verbosity_t.h>

#define MAX_PPL_SIZE 256

/**
   @brief Calculate popularity of characters from source file.

   @param[in] src Source file
   @param[out] dest_ppl Popularity array where calculated popularity will be stored.
   @param[in] verbose Verbosity level

   @return return number of read characters if succeed, 0 otherwise.
 */
long int
calculate_ppl(FILE* src, ppl_t *const dest_ppl,
              verbosity_t verbose);

/**
   @brief Read popularity of characters from source archive.

   @param[in] src Source archive file
   @param[out] dest_ppl Popularity array where read popularity will be stored.
   @param[in] num_code Number of characters to read.
   @param[in] verbose Verbosity level

   @return return number of read characters if succeed, 0 otherwise.
 */
long int
read_ppl(FILE* src, ppl_t *const dest_ppl,
         int num_code, verbosity_t verbose);

/**
   @brief Write array of characters popularity to destination file.

   @param[in] src_ppl Source popularity array
   @param[out] dest Destination file, where popularity will be stored.

   @return return number of written characters if succeed, 0 otherwise.
 */
int
write_ppl(const ppl_t *const src_ppl, FILE* dest);

/**
   @brief Return character with maximal popularity in source popularity array.

   @param[in] src_ppl Source popularity array

   @return Return character with maximal popularity
   in source popularity array, 0 if there were errors.
 */
int 
char_with_max_ppl(const ppl_t *const src_ppl);

#endif
