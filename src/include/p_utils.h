/**
   @file p_utils.h
   @brief Contains useful macroses for work with pointers
 */

#ifndef _P_UTILS_
#define _P_UTILS_

#ifdef _DEBUG_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define FREE(ptr)      \
  do {                 \
    if (ptr != NULL) { \
      free(ptr);       \
      ptr = NULL;      \
    }                  \
  } while (0)

#define CHKPTR(ptr)             \
  do {                          \
    if (ptr == NULL)            \
      printf("Bad ptr in %s: %u \n", __FILE__, __LINE__); \
  } while (0)

#else

#define FREE(ptr) /**/
#define CHKPTR(ptr) /**/

#endif /*_DEBUG_*/
#endif /*_P_UTILS_*/
