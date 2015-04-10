/**
   @file verbosity_t.h
   @brief Contains enumeration of verbosity levels.
   
   @author Roman Budny
 */

#ifndef _VERBOSITY_T_
#define _VERBOSITY_T_
/*@{*/
typedef enum {QUIET, /**< Supress all messages */
              INFO,  /**< Show information about archive */
              DEBUG  /**< Show all information 
                        about requested operation */
} verbosity_t;
/*@}*/ 
#endif
