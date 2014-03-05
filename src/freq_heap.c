#include <freq_heap.h>

void
init_heap(struct heap * h) 
/* Fill heap with null values. */
/* Set heap size to 0. */
{
  int i;

  for (i = 0; i < MAX_HEAP_SIZE; ++i)
    {
      h->data[i] = NULL;
    }
  h->size = 0;
}

void
fill_heap(ppl_t * src_ppl, struct heap * dest)
/* Fill heap with non-zero values from array of character popularity. */
/* Assume that source size == MAX_HEAP_SIZE */
{
  int i, heap_index;
  double total = 0;

  /* Calculate total number of characters */
  for (i = 0; i < MAX_HEAP_SIZE; ++i) 
    total += src_ppl[i];

  heap_index = 0;
  for (i = 0; i < MAX_HEAP_SIZE; ++i)
    {
      if (src_ppl[i] > 0)
	{
	  struct node_t * n = malloc(sizeof(struct node_t));
	  n->o_char = i; /* set character code */
	  n->freq = src_ppl[i] / total; /* calculate frequency */
	  n->left = NULL;
	  n->right = NULL;
	  dest->data[heap_index++] = n;
	}
    }
  dest->size = heap_index;
}

void
print_heap(struct heap * h)
/* Print heap values up to heap size. */
/* Assume that there are no null pointers in these places. */
{
  int i;
  puts("=== CHARACTER FREQUENCY HEAP ===");
  for (i = 0; i < h->size; i++)
    printf("%c: %f\n", h->data[i]->o_char, h->data[i]->freq);
  puts("================================");
  printf("Number of used characters: %i\n", h->size);
  puts("================================");
}

/* Core min heap functionality */
/* See T. H. Cormen, C. E. Leiserson "Introduction to Algorithms" */

inline void
swap(struct node_t * data[], int i, int j) 
/* Swap pointers in heap data array */
{
  struct node_t * n = data[i]; 
  data[i] = data[j];
  data[j] = n;
}

inline int
parent(int i)
{
  if (i)
    return (i-1)/2;
  else 
    return 0;
}

inline int
left(int i)
{
  return 2*i+1;
}

inline int
right(int i)
{
  return (i+1)*2;
}

void heapify(struct heap * h, int i)
/* Support heap property */
{
  int l = left(i);
  int r = right(i);
  int smallest;

  if ((l < h->size) && (h->data[l]->freq < h->data[i]->freq))
    smallest = l;
  else
    smallest = i;

  if ((r < h->size) && (h->data[r]->freq < h->data[smallest]->freq))
    smallest = r;

  if (smallest != i)
    {
      swap(h->data, i, smallest);
      heapify(h, smallest);
    }
}

void
build_heap(struct heap * h)
/* Make structure with heap properties */
{
  int i;
  for (i = (h->size/2)-1; i >= 0; i--)
    heapify(h, i);
}

struct node_t * 
heap_get_min(struct heap * h)
/* Return pointer to element with minimal frequency. */
/* Return NULL if heap is empty. */
{
   if (h->size < 1)
    return NULL;
   return h->data[0];
}

struct node_t *
heap_extract_min(struct heap * h)
/* Return pointer to element with minimal frequency
   and delete it from heap. */
/* Return NULL if heap is empty. */
{
  if (h->size == 0)
    return NULL;
  
  struct node_t * min = h->data[0];
  h->data[0] = h->data[(h->size)-1];
  h->data[(h->size)-1] = NULL;
  (h->size)--;

  heapify(h, 0);

  return min;
}

void
heap_insert(struct heap * h, struct node_t * src_node)
/* Insert node to heap. Assume that heap size < MAX_HEAP_SIZE */
{
  int i = (h->size)++;
  while ((i > 0) && (h->data[parent(i)]->freq > src_node->freq))
    {
      h->data[i] = h->data[parent(i)];
      i = parent(i);
    }
  h->data[i] = copy_node(src_node);
}
