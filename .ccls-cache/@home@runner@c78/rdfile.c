#include <stdio.h>
#include "dynmem.h"

char *rdfile(name)
const char name[];
{
  char c, *code;
  FILE *f = fopen(name, "r");
  int len = 0, j = 0;
  
  while ((c = getc(f)) != EOF)
    ++len;

  fseek(f, 0, 0);
  code = malloc(len);

  while ((c = getc(f)) != EOF)
    code[j++] = c;

  fclose(f);

  return code;
}
