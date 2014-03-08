#include <io_code.h>

void clear_code_buffer(code_t * code_buffer)
{
  int i;
  code_t zero = 0;

  for (i = 0; i < CODE_BUFFER_SIZE; ++i)
    {
      code_buffer[i] = zero;
    }
}

void export_data(FILE* dest, code_t * code_buffer, int elem_num)
/* store first elem_num elements of code_buffer to file */
{
  fwrite(code_buffer, sizeof(code_t), elem_num, dest); 
}

void compress_data(FILE* src, FILE* dest, struct hf_code * code_tbl, int verbose)
/* Compress contents of SRC with codes, specified in CODE_TBL,
   and save compressed variant to DEST */
{
  int c; /* character from input */
  int cur_buf_index = 0; /* current index in buffer */
  int cur_offset = 0; /* current offset in bit_set */
  int max_offset = sizeof(code_t)*8;

  code_t code_buffer[CODE_BUFFER_SIZE];
  clear_code_buffer(code_buffer);

  while ((c = fgetc(src)) != EOF)
    {
      int code_size = code_tbl[c].size;

      /* print_code(c, code_tbl[c]); */
      /* printf("cur_buf_index: %d\n", cur_buf_index); */
      /* printf("cur_offset: %d\n", cur_offset); */

      /* printf("=== INIT STATE OF OUTPUT BUFFER ===\n"); */
      /* printf("sz=%3d: ", cur_offset); */
      /* print_bits(code_buffer[0]); */
      /* printf(" "); */
      /* print_bits(code_buffer[1]); */
      /* printf("\n"); */
      /* printf("========================================\n\n"); */


      code_buffer[cur_buf_index] |= (code_tbl[c].code >> cur_offset);

      if (cur_offset + code_size < max_offset)
	/* enough space in cur code_t elem to place code */
	{
	  cur_offset += code_size;
	}
      else
	/* need to place it in separate code_t elements*/
	{
	  if (cur_buf_index < CODE_BUFFER_SIZE - 1) 
	    /* second part of code will be also placed in buffer */
	    {
	      cur_buf_index++;
	    }
	  else
	    /* end of buffer, we need to write compressed data to dest write rest to beginning */
	    {
	      export_data(dest, code_buffer, CODE_BUFFER_SIZE); /* write to dest*/
      
	      clear_code_buffer(code_buffer); /* clear buffer */
	      cur_buf_index = 0; /* reset index */
	    }

	  code_buffer[cur_buf_index] |= (code_tbl[c].code << (max_offset - cur_offset));
	  cur_offset -= (max_offset - code_size);
	}

      /* printf("cur_buf_index: %d\n", cur_buf_index); */
      /* printf("cur_offset: %d\n", cur_offset); */

      /* printf("=== END STATE OF OUTPUT BUFFER ===\n"); */
      /* printf("sz=%3d: ", cur_offset); */
      /* print_bits(code_buffer[0]); */
      /* printf(" "); */
      /* print_bits(code_buffer[1]); */
      /* printf("\n"); */
      /* printf("========================================\n\n"); */
    }
  if (cur_buf_index) /* we need to write rest to file */
    export_data(dest, code_buffer, cur_buf_index+1); /* write to dest*/
    
}

void
compress(char * src_filename, char * dest_filename, struct hf_code * code_tbl, int verbose)
/* Open and close needed files and call appropriate commpress function */
{
  if (src_filename == NULL && dest_filename == NULL)
    {
      compress_data(stdin, stdout, code_tbl, verbose);
    }
  else 
    if (src_filename == NULL && dest_filename != NULL)
      {
	FILE * destination = fopen(dest_filename, "w");

	compress_data(stdin, destination, code_tbl, verbose);

	fclose(destination);
      }
    else
      if (src_filename != NULL && dest_filename == NULL)
	{
	  FILE * source = fopen(src_filename, "r");

	  compress_data(source, stdout, code_tbl, verbose);

	  fclose(source);
	}
      else
	if (src_filename != NULL && dest_filename != NULL)
	  {
	    FILE * source = fopen(src_filename, "r");
	    FILE * destination = fopen(dest_filename, "wb");

	    compress_data(source, destination, code_tbl, verbose);

	    fclose(source);
	    fclose(destination);
	  }
}
