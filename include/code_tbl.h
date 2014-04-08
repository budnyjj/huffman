/** 
    @file code_tbl.h
    @brief Provides huffman code structure definition
    and some functions to work with it.

    @author Roman Budny
*/

#ifndef _CODE_TABLE_
#define _CODE_TABLE_

#include <bit_set.h>

#define MAX_CODE_TBL_SIZE 256
#define CODE_NOT_EXISTS -1

/*@{*/
struct hf_code {
  int size; /**< Size of significant part */
  code_t code; /**< Huffman code */
};
/*@}*/

/**
   @brief Print content of code table
   @param[in] tbl Array of huffman codes
*/
void 
print_code_tbl(const struct hf_code *const tbl);

#endif
