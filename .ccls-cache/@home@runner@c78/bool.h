#include "cross.h"

#ifndef BOOLCROSS
  #define BOOLCROSS
  
  #if C99
    #include <stdbool.h>
  #else
    #if C89
      typedef enum { false = 0, true = 1 } bool;
    #else
      #define false 0
      #define true 1
      typedef int bool
    #endif
  #endif
#endif
