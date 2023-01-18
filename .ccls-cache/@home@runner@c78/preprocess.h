#include "cross.h"
#include "iter.h"

#if C89
#else
typedef int void;
#endif

#ifndef PREPROCESS
  #define PREPROCESS
  
  itratr *preprocess();
  void prelex();
#endif
