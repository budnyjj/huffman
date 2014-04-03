#ifndef _IO_OPTIONS_
#define _IO_OPTIONS_

#include <command_t.h>
#include <verbosity_t.h>

struct io_options {
  command_t command;
  char * src_filename;
  char * dest_filename;
  verbosity_t verbose;
};

int
get_options(int argc, char ** argv,
            struct io_options *const dest_opts);

#endif
