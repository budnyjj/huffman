#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32

#include <win/wingetopt.h>
#include <win/unistd.h>

#else

#include <unistd.h>
#include <getopt.h>

#endif

#ifndef _HF_IO_
#define _HF_IO_

struct io_options {
  enum {CREATE, EXTRACT, NONE} command;
  char* filename;
  int verbose;
};

extern void
io_get_options(int argc, char *argv[], struct io_options *);

#endif
