/**
   @file node_t.h
   @brief Determines node type and
   functions to work with it

   @author Roman Budny
 */

#ifndef _NODE_T_
#define _NODE_T_

#include <stdlib.h>

#include <ppl_t.h>

#define NULL_CHAR -1

struct node_t;

/*@{*/
struct node_t 
{
  int o_char; /**< original character code */
  ppl_t ppl; /**< character popularity code */
  struct node_t * left; /**< pointer to left branch */
  struct node_t * right; /**< pointer to right branch */
};
/*@}*/

/**
   @brief Creates new node with safe values
 */
extern struct node_t *
init_node();

/**
   @brief Create new node and fills it with values from source

   @param[in] Source node
   @return Created node
 */
extern struct node_t *
copy_node(struct node_t * src_node);

#endif
