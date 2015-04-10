/**
   @file command_t.h
   @brief Contains enumeration of available compress commands.

   @author Roman Budnyjj
 */

#ifndef _COMMAND_T_
#define _COMMAND_T_

/*@{*/
typedef enum {
  NONE, /**< Nothing to do */
  CREATE, /**< Compress data */
  EXTRACT /**< Decompress data */
} command_t;
/*@}*/

#endif
