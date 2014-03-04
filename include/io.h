#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#ifndef _HF_IO_
#define _HF_IO_

struct io_options {
  enum {CREATE, EXTRACT, NONE} command;
  char* filename;
  int verbose;
};

extern struct io_options
io_get_options(int argc, char *argv[]);

#endif
