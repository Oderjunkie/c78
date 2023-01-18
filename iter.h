#include "cross.h"

#ifndef ITERATORS
  #define ITERATORS
  
  typedef struct itratr {
    void *current;
    void *state;
  #if C89
    void *(*next)();
  #else
    void *(*next)(void **state);
  #endif
  } itratr;
  
  void *itrnxt();
  void itrfre();
  
  itratr *range();
#endif
