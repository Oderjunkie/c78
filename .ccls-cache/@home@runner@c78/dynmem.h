#include "cross.h"

#ifndef DYNMEM
  #define DYNMEM
  #if C89
    #include <stddef.h>
    extern void *calloc(size_t, size_t);
    void cfree(char *);
  #else
    extern char *calloc();
    extern int cfree();
  #endif
  char *krmemcpy();
  int krstrcmp();
  char *falloc();
  int krstrlen();
#endif

#ifndef malloc
  #define malloc(x) calloc(1, x)
#endif

#ifndef free
  #define free(x) cfree((char *) x)
#endif
