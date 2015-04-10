/**
   @file io_options.h
   @brief tools for parse console arguments

   @author Roman Budny
 */

#ifndef _IO_OPTIONS_
#define _IO_OPTIONS_

#include <command_t.h>
#include <verbosity_t.h>

/*@{*/
struct io_options {
  command_t command; /**< Type of command, specified in command_t.h */
  char * src_filename; /**< Filename of source */
  char * dest_filename; /**< Filename of destination */
  verbosity_t verbose; /**< Type of verbosity, specified in verbosity_t.h */
};
/*@}*/


/**
   @brief Function for parsing cli options

   Get console arguments, parse and check them for correctness.
   @param[in] argc Number of console arguments
   @param[in] argv Array of console arguments
   @param[out] dest_opts Struct, where processed options will be stored
   @see init_options()
   @return 1 if succeed, 0 if there were errors
 */
int
get_options(int argc, char ** argv,
            struct io_options *const dest_opts);

#endif
