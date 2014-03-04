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
