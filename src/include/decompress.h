/**
   @file decompress.h
   @brief Contains decompress functions

   @author Roman Budny
 */

#ifndef _DECOMPRESS_
#define _DECOMPRESS_

#include <verbosity_t.h>

/**
   @brief Decompress source file and write it to destination
   
   This function provides interface for decompressing file with
   name, specified in src_fname, and write them to file with
   name, specified in dest_fname.

   @param[in] src_fname Filename of source
   @param[in] dest_fname Filename of destination
   @param[in] verbose Verbosity level
   
   @return 1 if succeed, 0 otherwise.
 **/
int
decompress(const char *const src_fname,
         const char *const dest_fname,
         verbosity_t verbose);

#endif
