/**
   @file ppl_heap.h
   @brief Provides popularity heap definition and realted functions to work with

   @author Roman Budny
 */

#ifndef _FREQ_HEAP_
#define _FREQ_HEAP_

#include <ppl_t.h>
#include <node_t.h>

#define MAX_HEAP_SIZE 256

/*@{*/
struct heap
{
  struct node_t * data[MAX_HEAP_SIZE]; /**< Array of heap elements */
  int size; /**< Size of heap */
};
/*@}*/

/**
   @brief Initialize heap with safe values

   Fill heap with null values.
   Set heap size to 0.

   @param[in] h Heap to work with
*/
void
init_heap(struct heap *const h);

/**
   @brief Fill heap with non-zero values from source popularity array

   Assume that source size == MAX_HEAP_SIZE

   @param[in] h Heap to work with
   @return 1 if succeed, 0 otherwise
*/ 
int
fill_heap(const ppl_t *const src_ppl, struct heap *const dest_heap);

/**
   @brief Refresh heap properties

   @param[in] h Heap to work with
*/
void
build_heap(struct heap *const h);

/**
   @brief Insert node to heap.

   Assume that heap size < MAX_HEAP_SIZE 

   @param[in] src_node Source node
   @param[out] dest_heap Destination heap
*/
void
heap_insert(struct node_t * src_node, struct heap *const dest_heap);


/**
   @brief Get node with minimal popularity.

   Assume that heap size < MAX_HEAP_SIZE 

   @param[in] h Heap to work with
   @return Return pointer to result or NULL if heap is empty.
*/
struct node_t *
heap_get_min(const struct heap *const h);

/**
   @brief Extract node [from heap] with minimal popularity.

   Assume that heap size < MAX_HEAP_SIZE 

   @param[in] h Heap to work with
   @return Return pointer to result or NULL if heap is empty.
*/
struct node_t *
heap_extract_min(struct heap *const h);

#endif
