#include <io.h>

const char* program_name;

void 
print_usage (FILE* stream, int exit_code)
{
  fprintf (stream, "Usage: %s [COMMAND...] [FILENAME]\n", program_name);
  fprintf (stream,
	   " -h --help\t Display this help message\n"
	   " -c --create\t Create a new archive\n");
  exit (exit_code);
}

struct io_options
make_options() {
  struct io_options options;
  options.command = NONE;
  options.filename = NULL;
  options.verbose = 0;
  return options;
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
	print_usage (stdout, 0);
	break;

      case 'v':
	options->verbose = 1;
	break;

      case 'x':
	options->command = EXTRACT;
	break;

      case '?': /* invalid option */
	print_usage (stderr, 1);
	break;

      default:
	abort (); /* smth else */
      }
  }

  int num_files = argc - optind;

  if (num_files == 1)
    options->filename = argv[optind];
  else if (num_files > 1)
    {
      puts("This program cannot work with "
	   "more than one file per launch!");
      print_usage(stderr, 1);
    }
}

void 
check_options (struct io_options * options)
{
  if (options->command == NONE) 
    {
      puts("Please specify COMMAND!");
      print_usage(stdout, 0);
    }

  if ((options->filename != NULL) &&
      (access(options->filename, R_OK) == -1))
    puts("Please specify existing file!");
}

struct io_options
io_get_options (int argc, char *argv[])
{
  struct io_options options = make_options();
  get_options(argc, argv, &options);
  check_options(&options);
  return options;
}

