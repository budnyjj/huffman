#ifndef _NODE_T_
#define _NODE_T_

#include <stdlib.h>

#include <ppl_t.h>

#define NULL_CHAR -1

struct node_t;

struct node_t 
{
  int o_char; /* original char code */
  ppl_t ppl;
  struct node_t * left;
  struct node_t * right;
};

extern struct node_t *
init_node();

extern struct node_t *
copy_node(struct node_t *);

#endif
