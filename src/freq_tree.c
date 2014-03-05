#include <freq_tree.h>

struct node_t *
build_tree(ppl_t * src_ppl, int verbose)
/* Build Huffman tree. */
/* Return pointer to tree root. */
{
  int i, num_of_chars = 0;

  struct heap h;

  init_heap(&h);
  fill_heap(src_ppl, &h);
  build_heap(&h);

  if (verbose)
    print_heap(&h);

  num_of_chars = h.size;
  for (i = 0; i < num_of_chars - 1; ++i)
    {
      struct node_t * n = init_node();
      n->left = heap_extract_min(&h);
      n->right = heap_extract_min(&h);
      n->freq = n->left->freq + n->right->freq;
      heap_insert(&h, n);
    }

  return heap_extract_min(&h);
}

void traverse_tree(struct node_t * cur_node, struct hf_code * code_tbl,
		   code_t cur_code, int cur_level,  code_t * bit_set)
/* Recursive traverse on NOT NULL tree. */
/* Assume that size of code_tbl >= maximal character code */
/* Assume that each not NULL_CHAR node have both children */
{
  if (cur_node->o_char != NULL_CHAR)
    {
      code_tbl[cur_node->o_char].code = cur_code;
      code_tbl[cur_node->o_char].size = cur_level;
      return;
    }
  else
    { 
      traverse_tree(cur_node->left, code_tbl,
		    cur_code | bit_set[cur_level],
		    cur_level + 1, bit_set);
	
      traverse_tree(cur_node->right, code_tbl,
		    cur_code, cur_level + 1, bit_set);
    }
}

void
tree_export_code(struct node_t * src_tree, struct hf_code * dest_code_tbl, int verbose)
/* Export character codes from huffman tree to code table */
{

  int init_level = 0;
  code_t init_code = 0;
  
  code_t bit_set[MAX_BIT_SET_SIZE]; /* array of bits with 2^i etc values, i -- index */ 
  fill_bit_set(bit_set);

  if (verbose)
    print_bit_set(bit_set); 
  
  if (src_tree != NULL)
    traverse_tree(src_tree, dest_code_tbl, init_code, init_level, bit_set);

  if (verbose)
    print_code_tbl(dest_code_tbl);
}
