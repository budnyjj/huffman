/**
   @file ppl.c
   @brief Popularity utilities
   @author Roman Budny
*/

#include <stdio.h>
#include <ppl.h>
#include <p_utils.h>

static void
clear_ppl(ppl_t *const ppl)
/* Fill ppl array with zeros */
{
  int i;
  for (i = 0; i < MAX_PPL_SIZE; ++i)
    ppl[i] = 0;
}

static void
print_ppl(const ppl_t *const ppl)
{
  int i, j;
  const int factor = 80; /* max bar chart width */

  ppl_t max_ppl = 0;

  for (i = 0; i < MAX_PPL_SIZE; i++)
    if (max_ppl < ppl[i])
      max_ppl = ppl[i];

  puts("=== CHARACTER POPULARITY TABLE ===");
  for (i = 0; i < MAX_PPL_SIZE; ++i)
    {
      int bar_width = (((double) ppl[i]) * factor) / max_ppl;
      printf("%c: %10ld [", i, ((long int) ppl[i]));
      for (j = 0; j < bar_width; ++j) 
        printf("#");
      printf("]\n");
    }
  puts("==================================");
}

/**
   @brief Calculate character popularity

   Calculate popularity of charaters from source file.

   @param src Source file
   @param dest_ppl Array of character popularities
   @param verbose Verbosity level
   @return Number of read characters if succeed, 0 otherwise.
 */
long int
calculate_ppl(FILE* src, ppl_t *const dest_ppl,
              verbosity_t verbose)
{
  int ch;
  long int total = 0L;

  CHKPTR(src);
  CHKPTR(dest_ppl);
  
  clear_ppl(dest_ppl);

  while ((ch = fgetc(src)) != EOF)
    {
      dest_ppl[ch]++;
      total++;
    }

  if (verbose == DEBUG)
    print_ppl(dest_ppl);

  return total;
}

/**
   @brief Read character popularity

   Write character popularity to destination file.
   Return offset of end.

   @param src_ppl Array of character popularities
   @param dest Destination file
   @return Number of coded characters if suceed, 0 otherwise
 */
int
write_ppl(const ppl_t *const src_ppl, FILE* dest)
/* Write character popularity to file */
/* Return number of coded characters if suceed, 0 otherwise */
{
  int i, num_code = 0;

  for (i = 0; i < MAX_PPL_SIZE; i++)
    if (src_ppl[i])
      num_code++;

  for (i = 0; i < MAX_PPL_SIZE; i++)
    if (src_ppl[i])
      {
        fwrite(&i, sizeof(i), 1, dest);
        fwrite(&src_ppl[i], sizeof(src_ppl[i]), 1, dest);
      }

  return num_code;
}

/**
   @brief Read character popularity

   Read character popularity from source file.
   Return offset of end.

   @param src Source file
   @param dest_ppl Array of character popularities
   @param num_code Number of character codes
   @param verbose Verbosity level
   @return Offset of end
 */
long int
read_ppl(FILE* src, ppl_t *const dest_ppl,
         int num_code, verbosity_t verbose)
{
  int i, ch;

  for (i = 0; i < num_code; i++)
    {
      fread(&ch, sizeof(ch), 1, src);
      fread(&dest_ppl[ch], sizeof(dest_ppl[ch]), 1, src);
    }

  if (verbose == DEBUG)
    print_ppl(dest_ppl);

  return ftell(src);
}

/**
   @brief Get code of character with maximmum popularity 

   Get code of character with maximmum popularity 

   @param src_ppl Array of character popularities
   @return Code of character with maximum polularity
 */
int 
char_with_max_ppl(const ppl_t *const src_ppl)
{
  int i, char_with_max_ppl = 0;
  ppl_t max_ppl = 0;

  CHKPTR(src_ppl);

  for (i = 0; i < MAX_PPL_SIZE; i++)
    {
      if (src_ppl[i] > max_ppl)
        {
          max_ppl = src_ppl[i];
          char_with_max_ppl = i;
        }
    }

  return char_with_max_ppl;
}
