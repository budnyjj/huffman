#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32 /* windows */

#include <win/wingetopt.h>
#include <win/unistd.h>

#else /* GNU */

#include <unistd.h>
#include <getopt.h>

#endif

#include <p_utils.h>
#include <io_options.h>

const char* program_name;

static void
print_usage (FILE* stream)
{

#ifdef _WIN32 /* windows */
  const char * usage_msg =
    " -c DEST_FILENAME  "
    "Create a new archive and store it in DEST_FILENAME\n"
    " -x DEST_FILENAME  "
    "Extract an existing archive to DEST_FILENAME\n"
    " -h                "
    "Display this help message\n"
    " -v                "
    "Display info messages\n"
    " -d                "
    "Display debug messages\n";

#else /* GNU */

  const char * usage_msg =
    " -c --create DEST_FILENAME   "
    "Create a new archive and store it in DEST_FILENAME\n"
    " -x --extract DEST_FILENAME  "
    "Extract an existing archive to DEST_FILENAME\n"
    " -h --help                   "
    "Display this help message\n"
    " -v --verbose                "
    "Display info messages\n"
    " -d --debug                  "
    "Display debug messages\n";

#endif

  fprintf (stream, "Usage: %s [COMMAND...] [SRC_FILENAME]\n", program_name);
  fprintf (stream, usage_msg);
}

static void
init_options(struct io_options *const opts)
/* Initialize options structure with default values */
{
  opts->command = NONE;
  opts->src_filename = NULL;
  opts->dest_filename = NULL;
  opts->verbose = QUIET;
}

static void
cli_get_options (int argc, char *const * argv,
             struct io_options *const options)
{
  int next_option = -1;
  int num_files;
  char * short_options = "c:dhvx:";

#ifdef __linux__

  const struct option long_options[] =
    {
      {"create", required_argument, NULL, 'c'},
      {"debug", required_argument, NULL, 'd'},
      {"help", no_argument, NULL, 'h'},
      {"extract", required_argument, NULL, 'x'},
      {"verbose", no_argument, NULL, 'v'},
      {NULL, 0, NULL, 0}
    };

#endif

  program_name = argv[0];

  while (1) {


#ifdef _WIN32

    next_option = getopt(argc, argv, short_options);

#else

    next_option = getopt_long(argc, argv, short_options,
                               long_options, NULL);

#endif

    if (next_option == -1)
      break;

    switch (next_option)
      {
      case 'c':
        {
          if (options->command == NONE)
            {
              options->command = CREATE;
              options->dest_filename = optarg;
            }
          else
            {
              fprintf(stderr,
                      "Please specify only one COMMAND!\n");
              print_usage (stderr);
              exit(1);
            }
          break;
        }
      case 'd':
        {
          options->verbose = DEBUG;
          break;
        }
      case 'h':
        {
          print_usage (stdout);
          exit(0);
        }
      case 'v':
        {
          options->verbose = INFO;
          break;
        }
      case 'x':
        {
          if (options->command == NONE)
            {
              options->command = EXTRACT;
              options->dest_filename = optarg;
            }
          else /* already specified command */
            {
              fprintf(stderr,
                      "Please specify only one COMMAND!\n");
              print_usage (stderr);
              exit(1);
            }
          break;
        }
      case '?': /* invalid option */
        {
          print_usage(stderr);
          exit(1);
        }
      default:
        abort (); /* smth else */
      }
  }

  num_files = argc - optind;

  if (num_files == 1)
    options->src_filename = argv[optind];
  else if (num_files > 1)
    {
      fprintf(stderr,
              "This program cannot work with "
              "more than one file per launch!\n");
      print_usage(stderr);
      exit(1);
    }
}

static int
get_file_size(const char *const filename)
{
  int file_size = 0;

  FILE* f = fopen(filename, "r");

  fseek(f, 0, SEEK_END);
  file_size = ftell(f);

  fclose(f);

  return file_size;
}

static void
check_options(const struct io_options *const options)
{
  if (options->command == NONE)
    {
      fprintf(stderr, "Please specify COMMAND!\n");
      print_usage(stderr);
      exit(1);
    }

  if (options->src_filename != NULL)
    {
      if (access(options->src_filename, R_OK) == -1) /* non-existing src*/
        {
          fprintf(stderr, "Please specify existing file!\n");
          exit(1);
        }
      if (!get_file_size(options->src_filename)) /* src is empty */
        {
          fprintf(stderr, "Please specify non-empty file!\n");
          exit(1);
        }
    }

}

void
get_options(int argc, char ** argv,
               struct io_options *const dest_opts)
{
  CHKPTR(argv);
  CHKPTR(dest_opts);

  init_options(dest_opts);
  cli_get_options(argc, argv, dest_opts);
  check_options(dest_opts);
}
