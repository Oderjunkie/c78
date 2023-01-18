#include "dynmem.h"

#if C89
  #undef free
  extern void free(void *);
  
  void cfree(mem)
  char *mem;
  {
    free(mem);
  }
  #include "dynmem.h"
#endif

char *krmemcpy(dst, src, bytes)
char *dst, *src;
size_t bytes;
{
  while (bytes--)
    *dst++ = *src++;
  
  return(dst);
}

/* K&R1, page 102 */
int krstrcmp(s, t) /* return <0 if s<t, 0 if s==t, >0 if s>t */
char *s, *t;
{
  for (; *s == *t; s++, t++)
    if (*s == '\0')
      return(0);
  return(*s - *t);
}

/* K&R1, page 98 */
int krstrlen(s)
char *s;
{
  char *p = s;
  
  while (*p != '\0')
    p++;
  
  return(p-s);
}

char *falloc(s)
char *s;
{
  char *t = malloc(krstrlen(s));
  krmemcpy(t, s, krstrlen(s));
  return t;
}
