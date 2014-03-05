#include <io.h>
#include <ppl.h>
#include <freq_tree.h> /* Explicit use for decoding */
#include <code_tbl.h>

int
main (int argc, char *argv[])
{
  struct io_options options;
  io_get_options(argc, argv, &options);

  switch (options.command) 
    {
    case CREATE:
      {
	ppl_t char_ppl[MAX_PPL_SIZE];
	calculate_ppl(options.filename, char_ppl, options.verbose);
	struct node_t * freq_tree = build_tree(char_ppl, options.verbose);
	
	struct hf_code char_code[MAX_CODE_TBL_SIZE];
	init_code_tbl(char_code);

	tree_export_code(freq_tree, char_code, options.verbose);

	break;
      }
    default:
      puts("This functionality was not implemented yet!");
      break;
    }
  
  exit (0);
}
