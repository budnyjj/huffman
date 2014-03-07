#include <stdio.h>

#include <ppl_t.h>
#include <node_t.h>
#include <code_t.h>

#include <code_tbl.h>
#include <bit_set.h>
#include <freq_heap.h>

#ifndef _FREQ_TREE_
#define _FREQ_TREE_

extern struct node_t *
build_tree(ppl_t *, int);

extern void
tree_export_code(struct node_t *, struct hf_code *, int);

#endif
