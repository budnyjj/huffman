#include <ppl.h>

void
clear_ppl(ppl_t * ppl)
/* Fill popularity array with zeros */
{
  int i;
  for (i = 0; i < MAX_PPL_SIZE; ++i)
    ppl[i] = 0;
}

void
get_ppl(FILE * source, ppl_t * dest_ppl)
/* Calculate symbols popularity. */
{
  int c = 0;

  while ((c = fgetc(source)) != EOF)
    {
      dest_ppl[c]++;
    }
}

void calculate_ppl(char * src_filename, ppl_t * dest_ppl, int verbose)
/* Calculate popularity of charaters from input source */
/* Available sources: FILE object if src_filename specified, stdin otherwise */
{
  clear_ppl(dest_ppl);
  if (src_filename == NULL)
    get_ppl(stdin, dest_ppl);
  else
    {
      FILE * source = fopen(src_filename, "r");     
      get_ppl(source, dest_ppl);
      fclose(source);
    }
  if (verbose)
    print_ppl(dest_ppl);
}

void
print_ppl(ppl_t * ppl) 
{
  int i, j;
  const int factor = 80; /* max bar chart width */
  
  ppl_t max_ppl = 0;

  for (i = 0; i < MAX_PPL_SIZE; i++)
    if (max_ppl < ppl[i])
      max_ppl = ppl[i];

  puts("=== CHARACTER POPULARITY TABLE ===");
  for (i = 0; i < MAX_PPL_SIZE; ++i)
    {
      int bar_width = (((double) ppl[i]) * factor) / max_ppl;
      printf("%c: %10ld [", i, ((long int) ppl[i]));
      for (j = 0; j < bar_width; ++j) 
	printf("#");
      printf("]\n");
    }
  puts("==================================");
}
