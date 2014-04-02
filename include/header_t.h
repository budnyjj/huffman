#ifndef _HEADER_
#define _HEADER_

struct header_t
{
  long int num_char;

  int num_code;

  /* code buffer size */
  int buffer_size; 

  int last_offset;
};

#endif
