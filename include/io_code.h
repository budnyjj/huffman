/**
   @file io_code.h
   @brief Determine output buffer size and provides functions 
   to work with it

   @author Roman Budnyjj
 */

#ifndef _IO_CODE_
#define _IO_CODE_

#include <bit_set.h>
#include <code_tbl.h>
#include <ppl_tree.h>
#include <verbosity_t.h>
#include <ppl_t.h>

#define CODE_BUFFER_SIZE 1024 /* how to determine optimal size? */

/**
   @brief Fill code buffer with zero values

   @param[out] code_buffer Code buffer to work with
 */
void clear_code_buffer(code_t *const code_buffer);

#endif
