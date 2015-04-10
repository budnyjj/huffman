/**
   @file ppl_tree.h

   @brief Provides functions to work with huffman tree
   @author Roman Budny
 */

#ifndef _FREQ_TREE_
#define _FREQ_TREE_

#include <ppl_t.h>
#include <node_t.h>
#include <code_t.h>
#include <verbosity_t.h>

#include <code_tbl.h>
#include <ppl_heap.h>

/**
   @brief Build huffman tree using data from array of characters popularity

   @param[in] Source array of characters popularity
   @return pointer to tree root if succeed, NULL otherwise
 */
struct node_t *
build_tree(const ppl_t *const src_ppl);

/**
   @brief Export huffman codes from tree to array of codes

   @param[in] Source huffman tree 
   @param[out] Destination array of codes
   @param verbose Verbosity level
 */
void
tree_export_code(const struct node_t *const src_tree,
                 struct hf_code *const dest_code_tbl,
                 verbosity_t verbose);

/**
   @brief Free contents of popularity tree

   @param ppl_tree Source tree
 */
void
clear_tree(struct node_t * ppl_tree);

#endif
