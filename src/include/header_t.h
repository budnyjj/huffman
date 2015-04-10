/**
   @file header_t.h

   @brief Provides definition of struct which
   contains information about archive.

   @author Roman Budny
 */

#ifndef _HEADER_
#define _HEADER_

/*@{*/
struct header_t
{
  long int num_char; /**< Number of encoded characters */

  int num_code; /**< Number of used huffman codes */

  int buffer_size;  /**< Size of code buffer */

  int last_offset; /**< Offset in last byte of compressed data */
};
/*@}*/

#endif
