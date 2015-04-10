/**
   @file compress.h
   @brief Contains compress functions

   @author Roman Budny
 */

#ifndef _COMPRESS_
#define _COMPRESS_

#include <verbosity_t.h>

/**
   @brief Compress source file and write it to destination
   
   This function provides interface for compressing file with
   name, specified in src_fname, and write them to file with
   name, specified in dest_fname.

   @param[in] src_fname Filename of source
   @param[in] dest_fname Filename of destination
   @param[in] verbose Verbosity level
   
   @return 1 if succeed, 0 otherwise.
 **/
int
compress(const char *const src_fname,
         const char *const dest_fname,
         verbosity_t verbose);

#endif
