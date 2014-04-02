#include <stdlib.h>
#include <stdio.h>

#include <ppl_heap.h>
#include <p_utils.h>

void
init_heap(struct heap *const h)
/* Fill heap with null values. */
/* Set heap size to 0. */
{
  int i;

  CHKPTR(h);

  for (i = 0; i < MAX_HEAP_SIZE; ++i)
    {
      h->data[i] = NULL;
    }
  h->size = 0;
}

static void
clear_heap(struct heap *const h, int max_index)
/* Free allocated memory for heap elements in range [0; max_index] */
{
  int i;

  CHKPTR(h);

  for (i = 0; i < max_index; ++i)
    {
      FREE(h->data[i]);
    }
  h->size = 0;
}

int
fill_heap(const ppl_t *const src_ppl, struct heap *const dest)
/* Fill heap with non-zero values from array of character popularity. */
/* Assume that source size == MAX_HEAP_SIZE */
/* Return 1 if succeed, 0 otherwise */
{
  int i, heap_index;

  CHKPTR(src_ppl);
  CHKPTR(dest);

  heap_index = 0;
  for (i = 0; i < MAX_HEAP_SIZE; ++i)
    {
      if (src_ppl[i]) /* Non zero popularity */
        {
          struct node_t * n = malloc(sizeof(struct node_t));

          if (n)
            {
              n->o_char = i; /* set character code */
              n->ppl = src_ppl[i]; /* set popularity */
              n->left = NULL;
              n->right = NULL;
              dest->data[heap_index] = n;
              heap_index++;
            }
          else
            {
              FREE(n);
              clear_heap(dest, heap_index + 1);
              return 0;
            }
        }
    }

  dest->size = heap_index;
  return 1;
}

/* Core min heap functionality */
/* See T. H. Cormen, C. E. Leiserson "Introduction to Algorithms" */

static void
swap(struct node_t * data[], int i, int j)
/* Swap pointers in heap data array */
{
  struct node_t * pi = data[i];
  data[i] = data[j];
  data[j] = pi;
}

static int
parent(int i)
{
  if (i)
    return (i-1)/2;
  else
    return 0;
}

static int
left(int i)
{
  return 2*i+1;
}

static int
right(int i)
{
  return (i+1)*2;
}

static void
heapify(struct heap *const h, int i)
/* Support heap property */
{
  int l = left(i);
  int r = right(i);
  int smallest;

  if ((l < h->size) && (h->data[l]->ppl < h->data[i]->ppl))
    smallest = l;
  else
    smallest = i;

  if ((r < h->size) && (h->data[r]->ppl < h->data[smallest]->ppl))
    smallest = r;

  if (smallest != i)
    {
      swap(h->data, i, smallest);
      heapify(h, smallest);
    }
}

void
build_heap(struct heap *const h)
/* Make structure with heap properties */
{
  int i;

  CHKPTR(h);

  for (i = (h->size/2)-1; i >= 0; i--)
    heapify(h, i);
}

struct node_t *
heap_get_min(const struct heap *const h)
/* Return pointer to element with minimal popularity. */
/* Return NULL if heap is empty. */
{
  CHKPTR(h);

  if (h->size < 1)
    return NULL;
  return h->data[0];
}

struct node_t *
heap_extract_min(struct heap *const h)
/* Return pointer to element with minimal popularity
   and delete it from heap. */
/* Return NULL if heap is empty. */
{
  struct node_t * min;

  CHKPTR(h);

  if (h->size == 0)
    return NULL;

  min = h->data[0];
  h->data[0] = h->data[(h->size)-1];
  h->data[(h->size)-1] = NULL;
  (h->size)--;

  heapify(h, 0);

  return min;
}

void
heap_insert(struct heap *const h, struct node_t * src_node)
/* Insert node to heap. Assume that heap size < MAX_HEAP_SIZE */
{
  int i = (h->size)++;

  CHKPTR(h);
  CHKPTR(src_node);

  while ((i > 0) && (h->data[parent(i)]->ppl > src_node->ppl))
    {
      h->data[i] = h->data[parent(i)];
      i = parent(i);
    }
  h->data[i] = src_node;
}
