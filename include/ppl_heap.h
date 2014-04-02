#ifndef _FREQ_HEAP_
#define _FREQ_HEAP_

#include <ppl_t.h>
#include <node_t.h>

#define MAX_HEAP_SIZE 256

struct heap
{
  struct node_t * data[MAX_HEAP_SIZE];
  int size;
};

void
init_heap(struct heap *const);

int
fill_heap(const ppl_t *const, struct heap *const);

void
build_heap(struct heap *const);

void
heap_insert(struct heap *const, struct node_t *);

struct node_t *
heap_get_min(const struct heap *const);

struct node_t *
heap_extract_min(struct heap *const);

#endif
