#ifndef _FREQ_TREE_
#define _FREQ_TREE_

#include <ppl_t.h>
#include <node_t.h>
#include <code_t.h>
#include <verbosity_t.h>

#include <code_tbl.h>
#include <ppl_heap.h>

struct node_t *
build_tree(const ppl_t *const, verbosity_t);

void
tree_export_code(const struct node_t *const,
                 struct hf_code *const,
                 verbosity_t);

void
clear_tree(struct node_t *);

#endif
