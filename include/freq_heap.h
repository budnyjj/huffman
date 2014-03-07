#include <stdlib.h>
#include <stdio.h>

#include <ppl_t.h>
#include <node_t.h>

#ifndef _FREQ_HEAP_
#define _FREQ_HEAP_

#define MAX_HEAP_SIZE 256

struct heap 
{
  int size;
  struct node_t * data[MAX_HEAP_SIZE];
};

extern void  
init_heap(struct heap *);

extern void
fill_heap(ppl_t *, struct heap *);

extern void
build_heap(struct heap *);

extern void
heap_insert(struct heap *, struct node_t *);

extern struct node_t *
heap_extract_min(struct heap *);

extern void
print_heap(struct heap *);

#endif
