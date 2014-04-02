#include <stdio.h>
#include <ppl_tree.h>
#include <bit_set.h>
#include <p_utils.h>

static void
export_code(const struct node_t *const cur_node,
            struct hf_code *const code_tbl,
            code_t cur_code,
            int cur_level,
            const code_t *const bit_set)
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
      export_code(cur_node->left, code_tbl,
                    cur_code | bit_set[cur_level],
                    cur_level + 1, bit_set);

      export_code(cur_node->right, code_tbl,
                    cur_code, cur_level + 1, bit_set);
    }
}

struct node_t *
build_tree(const ppl_t *const src_ppl, verbosity_t verbose)
/* Build Huffman tree. */
/* Set dest_tree to the tree root if there were no errors, NULL otherwise. */
/* Return heap build status -> see header*/
{
  struct heap h;

  CHKPTR(src_ppl);

  init_heap(&h);

  if (fill_heap(src_ppl, &h)) /* succeed memory allocation */
    {
      int i, num_of_chars = 0;

      build_heap(&h);

      num_of_chars = h.size;
      for (i = 0; i < num_of_chars - 1; ++i)
        {
          struct node_t * n = init_node();
          n->left = heap_extract_min(&h);
          n->right = heap_extract_min(&h);
          n->ppl = n->left->ppl + n->right->ppl;
          heap_insert(&h, n);
        }

      CHKPTR(heap_get_min(&h)); /* test ptr value */
      return heap_extract_min(&h);
    }
  else
    return NULL;
}

void
tree_export_code(const struct node_t *const src_tree,
                 struct hf_code *const dest_code_tbl,
                 verbosity_t verbose)
/* Export character codes from huffman tree to code table */
{
  int init_level = 0;
  code_t init_code = 0;

  code_t bit_set[MAX_BIT_SET_SIZE]; /* array of bits with 2^i LSB values, i -- index */ 

  CHKPTR(src_tree);
  CHKPTR(dest_code_tbl);

  fill_bit_set_pos(bit_set);

  if (verbose == DEBUG)
    print_bit_set(bit_set);

  export_code(src_tree, dest_code_tbl, init_code, init_level, bit_set);

  if (verbose == DEBUG)
    print_code_tbl(dest_code_tbl);
}

static void
clear_node(struct node_t * cur_node)
/* Free memory, which was allocated for popularity tree */
/* Assume that each not NULL_CHAR node have both children */
{
  if (cur_node->o_char == NULL_CHAR)
    {
      clear_node(cur_node->left);
      clear_node(cur_node->right);
    }
  FREE(cur_node);
}


void
clear_tree(struct node_t * ppl_tree)
/* Wrapper around recursive function clear_node */
{
  CHKPTR(ppl_tree);
  clear_node(ppl_tree);
}
