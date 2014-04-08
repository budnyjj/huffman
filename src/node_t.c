#include <node_t.h>

struct node_t *
init_node()
{
  struct node_t * n = calloc(1, sizeof(struct node_t));
  n->o_char = NULL_CHAR;
  n->left = NULL;
  n->right = NULL;

  return n;
}

struct node_t *
copy_node(struct node_t * src_node)
/* Return pointer to copy of source node */
{
  struct node_t * dest_node = malloc(sizeof(struct node_t));
  dest_node->o_char = src_node->o_char;
  dest_node->ppl = src_node->ppl;
  dest_node->left = src_node->left; 
  dest_node->right = src_node->right;

  return dest_node;
}
