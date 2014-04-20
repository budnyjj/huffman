/**
   @file hf.c
   @brief Main function
   @author Roman Budny
*/

#include <stdio.h>
#include <stdlib.h>

#include <io_options.h>
#include <compress.h>
#include <decompress.h>

/**
   @brief Main function
   @param[in] argc Number of console arguments
   @param[in] argv Array of  console arguments
   @return 0 if success, 1 if fail
 */
int
main (int argc, char *argv[])
{

  struct io_options options;
  if (!get_options(argc, argv, &options))
    exit(1);

  switch (options.command)
    {
    case CREATE:
      {
        if (!compress(options.src_filename, options.dest_filename,
                      options.verbose))
          {
            fprintf(stderr, "Some errors happened. Aborting.\n");
            exit(1);
          }
	break;
      }
    case EXTRACT:
      {
        if (!decompress(options.src_filename,
                        options.dest_filename,
                        options.verbose))
          {
            fprintf(stderr, "Some errors happened. Aborting.\n");
            exit(1);
          }
        break;
      }
    default:
      puts("This functionality was not implemented yet!");
      break;
    }
  
  exit (0);
}
