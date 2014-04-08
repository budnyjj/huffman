#include <stdio.h>

#include <decompress.h>

#include <ppl.h>
#include <ppl_tree.h>
#include <bit_set.h>
#include <io_code.h>
#include <p_utils.h>
#include <header_t.h>

static void
read_data(FILE* src, FILE* dest,
          const struct node_t *const ppl_tree,
          struct header_t archive_info,
          verbosity_t verbose)
{
  int cur_elem_num = 0;

  int max_offset = sizeof(code_t)*8;
  code_t code_buffer[CODE_BUFFER_SIZE];
  code_t bit_set[MAX_BIT_SET_SIZE];
  const struct node_t * cur_node = ppl_tree;

  CHKPTR(src);
  CHKPTR(dest);
  CHKPTR(ppl_tree);

  fill_bit_set_pos(bit_set);
  clear_code_buffer(code_buffer);

  while ((cur_elem_num =
          fread(code_buffer, sizeof(code_t), archive_info.buffer_size, src))) 
    {
      int i, j;

      if (!feof(src)) /* this is not end of file */
        {
          for (i = 0; i < cur_elem_num; i++)
            {
              for (j = 0; j < max_offset; j++)
                {
                  if (cur_node->o_char != NULL_CHAR) /* found char */
                    {
                      fputc(cur_node->o_char, dest);
                      cur_node = ppl_tree;
                    }
                  if (code_buffer[i] & bit_set[j])
                    cur_node = cur_node->left;
                  else
                    cur_node = cur_node->right;
                }
            }
        }
      else /* this is end of file */
        {
          for (i = 0; i < cur_elem_num - 1; i++) /* read all except last elem*/
            {
              for (j = 0; j < max_offset; j++)
                {
                  if (cur_node->o_char != NULL_CHAR) /* found char */
                    {
                      fputc(cur_node->o_char, dest);
                      cur_node = ppl_tree;
                    }
                  if (code_buffer[i] & bit_set[j])
                    cur_node = cur_node->left;
                  else
                    cur_node = cur_node->right;
                }
            }
          for (j = 0; j < archive_info.last_offset; j++) /*read last elem in code buffer */
            {
              if (cur_node->o_char != NULL_CHAR) /* found char */
                {
                  fputc(cur_node->o_char, dest);
                  cur_node = ppl_tree;
                }
              if (code_buffer[cur_elem_num - 1] & bit_set[j])
                cur_node = cur_node->left;
              else
                cur_node = cur_node->right;
            }
        }
    }
}


static void
read_archive(const char* src_fname, const char* dest_fname,
             const struct node_t *const ppl_tree,
             struct header_t archive_info, long int data_offset,
             verbosity_t verbose) 
/* Read and decompress data from src and store it in dest */
{
  FILE* src_file = NULL;
  FILE* dest_file = NULL;
  
  src_file = fopen(src_fname, "rb");
  fseek(src_file, data_offset, SEEK_SET);


  dest_file = fopen(dest_fname, "w");
  read_data(src_file, dest_file,
            ppl_tree, archive_info, verbose);
  fclose(dest_file);
  dest_file = NULL;

  fclose(src_file);
  src_file = NULL;
}

void
read_single_char(const ppl_t *const src_ppl,
                 const char *const dest_fname,
                 long int num_char)
{
  int i, single_char;

  CHKPTR(src_ppl);
  CHKPTR(dest_fname);

  single_char = char_with_max_ppl(src_ppl);

  FILE* dest_file = fopen(dest_fname, "w");
  for (i = 0; i < num_char; i++)
    fputc(single_char, dest_file);

  fclose(dest_file);
}

int
decompress(const char *const src_fname,
         const char *const dest_fname,
         verbosity_t verbose)
/* Decompress contents of src and write it to dest */
/* Return 1 if succeed, 0 otherwise */
{
  ppl_t char_ppl[MAX_PPL_SIZE] = {0};
  struct header_t archive_info = {0, 0, 0}; /* contains info about archive */
  long int data_offset = 0;
  FILE* src_file = NULL;

  CHKPTR(src_fname);
  CHKPTR(dest_fname);

  src_file = fopen(src_fname, "r");
  fread(&archive_info, sizeof(archive_info), 1, src_file);
  data_offset = read_ppl(src_file, char_ppl, archive_info.num_code, verbose);
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

  if (archive_info.num_code == 1) /* src file contatins data of single character */
    {
      read_single_char(char_ppl, dest_fname, archive_info.num_char);
    }
  else
    {
      struct node_t * ppl_tree = NULL; 
      ppl_tree = build_tree(char_ppl);
      if (!ppl_tree)
        {
          fprintf(stderr, "Error of memory allocation!\n");
          return 0;
        }

      read_archive(src_fname, dest_fname, ppl_tree,
                   archive_info, data_offset, verbose);

      clear_tree(ppl_tree);
    }

  return 1;
}
