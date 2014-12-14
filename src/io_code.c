/**
   @file io_code.c
   @brief I/O code utils
   @author Roman Budny
*/

#include <io_code.h>
#include <bit_set.h>

/**
   @brief Clear code buffer
   @param code_buffer Code buffer
 */
void clear_code_buffer(code_t *const code_buffer)
{
  int i;

  for (i = 0; i < CODE_BUFFER_SIZE; ++i)
    {
      code_buffer[i] = 0;
    }
}
