/**
   @file ppl_tree.c
   @brief Huffman tree utilities
   @author Roman Budny
*/

#include <stdio.h>
#include <ppl_tree.h>
#include <bit_set.h>
#include <p_utils.h>

/* Recursive traverse on NOT NULL tree. */
/* Assume that size of code_tbl >= maximal character code */
/* Assume that each not NULL_CHAR node have both children */
static void
export_code(const struct node_t *const cur_node,
            struct hf_code *const code_tbl,
            code_t cur_code,
            int cur_level,
            const code_t *const bit_set)
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

/**
   @brief Build Huffman tree based on character popularity 

   Build Huffman tree based on character popularity

   @param src_ppl Array of character popularities
   @return Pointer to the root of Huffman tree
 */
struct node_t *
build_tree(const ppl_t *const src_ppl)
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
          heap_insert(n, &h);
        }

      CHKPTR(heap_get_min(&h)); /* test ptr value */
      return heap_extract_min(&h);
    }
  else
    return NULL;
}

/**
   @brief Export character codes from Huffman tree to code table

   Export character codes from Huffman tree to code table

   @param src_tree Huffman tree
   @param dst_code_tbl Destination code table
   @param verbose Level of verbosity
 */
void
tree_export_code(const struct node_t *const src_tree,
                 struct hf_code *const dst_code_tbl,
                 verbosity_t verbose)
{
  int init_level = 0;
  code_t init_code = 0;

  code_t bit_set[MAX_BIT_SET_SIZE]; /* array of bits with 2^i LSB values, i -- index */ 

  CHKPTR(src_tree);
  CHKPTR(dst_code_tbl);

  fill_bit_set_pos(bit_set);

  if (verbose == DEBUG)
    print_bit_set(bit_set);

  export_code(src_tree, dst_code_tbl, init_code, init_level, bit_set);

  if (verbose == DEBUG)
    print_code_tbl(dst_code_tbl);
}

/* Free memory, which was allocated for popularity tree */
/* Assume that each not NULL_CHAR node have both children */
static void
clear_node(struct node_t * cur_node)
{
  if (cur_node->o_char == NULL_CHAR)
    {
      clear_node(cur_node->left);
      clear_node(cur_node->right);
    }
  FREE(cur_node);
}

/**
   @brief Clear all data from Huffman data

   Clear all data from Huffman data.
   This is a wrapper around recursive function clear_node.

   @param ppl_tree Huffman tree
 */
void
clear_tree(struct node_t * ppl_tree)
{
  CHKPTR(ppl_tree);
  clear_node(ppl_tree);
}
