#include <io.h>

const char* program_name;

void 
print_usage (FILE* stream)
{
  fprintf (stream, "Usage: %s [COMMAND...] [FILENAME]\n", program_name);
  fprintf (stream,
	   " -h --help\t Display this help message\n"
	   " -c --create\t Create a new archive\n"
	   " -v --verbose\t Display info and debug messages\n");
}

void
init_options(struct io_options * opts) {
  opts->command = NONE;
  opts->filename = NULL;
  opts->verbose = 0;
}

void
get_options (int argc, char *argv[], struct io_options * options)
{
  int next_option;
  program_name = argv[0];
  const char* const short_options = "chvx";
  const struct option long_options[] =
    {
      {"help", no_argument, NULL, 'h' },
      {"create", no_argument, NULL, 'c'},
      {"extract", no_argument, NULL, 'x'},
      {"verbose", no_argument, NULL, 'v'},
      {NULL, 0, NULL, 0}
    };

  while (1) {
    next_option = getopt_long (argc, argv, short_options,
			       long_options, NULL);

    if (next_option == -1)
      break;

    switch (next_option)
      {
      case 'c':
	options->command = CREATE;
	break;

      case 'h': 
	{
	  print_usage (stdout);
	  exit(0);
	}
      case 'v':
	options->verbose = 1;
	break;

      case 'x':
	options->command = EXTRACT;
	break;

      case '?': /* invalid option */
	{
	  print_usage(stderr);
	  exit(1);
	}
      default:
	abort (); /* smth else */
      }
  }

  int num_files = argc - optind;

  if (num_files == 1)
    options->filename = argv[optind];
  else if (num_files > 1)
    {
      fprintf(stderr,
	      "This program cannot work with "
	      "more than one file per launch!\n");
      print_usage(stderr);
      exit(1);
    }
}

void 
check_options(struct io_options * options)
{
  if (options->command == NONE) 
    {
      fprintf(stderr, "Please specify COMMAND!\n");
      print_usage(stderr);
      exit(1);
    }

  if ((options->filename != NULL) &&
      (access(options->filename, R_OK) == -1))
    {
      fprintf(stderr, "Please specify existing file!\n");
      exit(1);
    }
}

void
io_get_options(int argc, char *argv[], struct io_options * dest_opts)
{
  init_options(dest_opts);
  get_options(argc, argv, dest_opts);
  check_options(dest_opts);
}

