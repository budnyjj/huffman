#include <io_options.h>
#include <ppl.h>
#include <freq_tree.h> /* Explicit use for decoding */
#include <code_tbl.h>
#include <io_code.h>

int
main (int argc, char *argv[])
{
  struct io_options options;
  io_get_options(argc, argv, &options);

  switch (options.command) 
    {
    case CREATE:
      {
	struct node_t * freq_tree;
	struct hf_code char_code[MAX_CODE_TBL_SIZE];

	ppl_t char_ppl[MAX_PPL_SIZE];
	calculate_ppl(options.src_filename, char_ppl, options.verbose);
	freq_tree = build_tree(char_ppl, options.verbose);
	
	init_code_tbl(char_code);

	tree_export_code(freq_tree, char_code, options.verbose);

	compress(options.src_filename, "out/res.txt", char_code, options.verbose);

	break;
      }
    default:
      puts("This functionality was not implemented yet!");
      break;
    }
  
  exit (0);
}
