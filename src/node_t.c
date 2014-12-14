/**
   @file node_t.c
   @brief Node utils
   @author Roman Budny
*/

#include <node_t.h>

/**
   @brief Initialize node
   @return Node with safe values
 */
struct node_t *
init_node()
{
  struct node_t * n = calloc(1, sizeof(struct node_t));
  n->o_char = NULL_CHAR;
  n->left = NULL;
  n->right = NULL;

  return n;
}

/**
   @brief Copy node

   @param src_node Source node
   @return Pointer to copy of source node
 */
struct node_t *
copy_node(struct node_t * src_node)
{
  struct node_t * dest_node = malloc(sizeof(struct node_t));
  dest_node->o_char = src_node->o_char;
  dest_node->ppl = src_node->ppl;
  dest_node->left = src_node->left; 
  dest_node->right = src_node->right;

  return dest_node;
}
