/**
   @file compress.c
   @brief Provides compress functionality

   @author Roman Budny
*/

#include <stdio.h>

#include <compress.h>

#include <ppl.h>
#include <ppl_tree.h>
#include <code_tbl.h>
#include <io_code.h>
#include <p_utils.h>
#include <header_t.h>

/** @brief Compress and write src contents to destination
    
    Compress contents of src with codes, specified in code_tbl,
    and write variant to dest.

    @param src Source file
    @param dest Destination file
    @param char_code Array of huffman codes
    @param archive_info Information about archive
    @param verbose Verbosity level
 */
static void
write_data(FILE* src, FILE* dest, 
           const struct hf_code *const code_tbl,
           struct header_t *const archive_info,
           verbosity_t verbose)
{
  int ch; /* character from input */
  int cur_buf_index = 0; /* current index in buffer */
  int cur_offset = 0; /* current offset in bit_set */
  int max_offset = sizeof(code_t)*8;

  code_t code_buffer[CODE_BUFFER_SIZE];

  CHKPTR(src);
  CHKPTR(dest);
  CHKPTR(code_tbl);
  CHKPTR(archive_info);

  clear_code_buffer(code_buffer);

  archive_info->buffer_size = CODE_BUFFER_SIZE;

  while ((ch = fgetc(src)) != EOF)
    {
      int code_size = code_tbl[ch].size;

      code_buffer[cur_buf_index] |= (code_tbl[ch].code >> cur_offset);

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
	    /* end of buffer, we need to write compressed data
               to dest write rest to beginning */
	    {
              fwrite(code_buffer, sizeof(code_t), CODE_BUFFER_SIZE, dest); 
      
	      clear_code_buffer(code_buffer); 
	      cur_buf_index = 0; /* reset index */
	    }
	  code_buffer[cur_buf_index] |= (code_tbl[ch].code << (max_offset - cur_offset));
	  cur_offset -= (max_offset - code_size);
	}
    }
  if (cur_offset || cur_buf_index) /* we need to write rest to file */
    {
      fwrite(code_buffer, sizeof(code_t), cur_buf_index + 1, dest);    
      clear_code_buffer(code_buffer);
    }  
 
  if (verbose == DEBUG)
    printf("END DATA POSITION: %ld\n", ftell(dest));

  archive_info->last_offset = cur_offset + 1;
}

/** @brief Make archive from source contents and write it to destination
    
    This function wraps write_data function

    @param src_fname Filename of source
    @param dest_fname Filename of destination
    @param char_ppl Array of character popularity
    @param char_code Array of huffman codes
    @param archive_info Information about archive
    @param verbose Verbosity level

    @see write_data

    @return 1 if succeed, 0 otherwise
 */
static int
write_archive(const char *const src_fname, const char *const dest_fname,
              const ppl_t *const char_ppl,
              const struct hf_code *const char_code,
              struct header_t archive_info, verbosity_t verbose)
{
  FILE* src_file = NULL;
  FILE* dest_file = fopen(dest_fname, "wb");

  CHKPTR(char_ppl);
  CHKPTR(char_code);

  if (verbose == DEBUG)
    printf("HEADER INFO POSITION: %ld\n", ftell(dest_file));

  /* Reserve place for header at the beginning of dest_file */
  fwrite(&archive_info, sizeof(archive_info), 1, dest_file);
      
  if (verbose == DEBUG)
    printf("BEGIN OF HUFFMAN CODES POSITION: %ld\n", ftell(dest_file));

  archive_info.num_code = write_ppl(char_ppl, dest_file);

  if (!archive_info.num_code)
    {
      fprintf(stderr, "Can't export character popularity to archive!\n");
      fclose(dest_file);
      return 0;
    }

  if (verbose == DEBUG)
    printf("BEGIN OF ENCODED CHARACTERS POSITION: %ld\n", ftell(dest_file));

  src_file = fopen(src_fname, "r");
  write_data(src_file, dest_file, char_code, &archive_info, verbose);
  fclose(src_file);
  src_file = NULL;

  if (verbose == DEBUG)
    {
      printf("=== ARCHIVE INFO ===\n");
      printf("NUMBER OF ENCODED CHARACTERS: %ld\n", archive_info.num_char);
      printf("NUMBER OF CODES: %d\n", archive_info.num_code);
      printf("CODE BUFFER SIZE: %d\n", archive_info.buffer_size);
      printf("OFFSET IN LAST BYTE: %d\n", archive_info.last_offset);
    }

  /* Update header info at the beginning of dest_file */
  fseek(dest_file, 0, SEEK_SET);
  fwrite(&archive_info, sizeof(archive_info), 1, dest_file);

  fclose(dest_file);
  dest_file = NULL;

  return 1;
}

int
compress(const char *const src_fname,
         const char *const dest_fname,
         verbosity_t verbose)
{
  ppl_t char_ppl[MAX_PPL_SIZE] = {0};
  struct node_t * ppl_tree = NULL; 
  struct hf_code char_code[MAX_CODE_TBL_SIZE] = {{0, CODE_NOT_EXISTS}};
  struct header_t archive_info = {0}; /* contains info about archive */

  FILE* src_file = NULL;

  CHKPTR(src_fname);
  CHKPTR(dest_fname);
  
  src_file = fopen(src_fname, "r");
  archive_info.num_char = calculate_ppl(src_file, char_ppl, verbose);
  fclose(src_file);
  
  if (!archive_info.num_char)
    {
      fprintf(stderr, "Can't read source!\n");
      return 0;
    }

  ppl_tree = build_tree(char_ppl);

  if (!ppl_tree)
    {
      fprintf(stderr, "Error of memory allocation!\n");
      return 0;
    }

  tree_export_code(ppl_tree, char_code, verbose);
  clear_tree(ppl_tree);

  return write_archive(src_fname, dest_fname,
                       char_ppl, char_code,
                       archive_info, verbose);
}
