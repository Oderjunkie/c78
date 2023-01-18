#include <stdio.h>
#include "lexer.h"
#include "dynmem.h"
#include "preprocess.h"
#include "rdfile.h"
#include "iter.h"

char *strtyp(type)
tokentype type;
{
  switch (type) {
  
#define X(T, V) case T: return #T;
#include "tokens.def"
  
#if C89
#else
  default:
    return "ERROR_TOKEN";
#endif
  }
}

int main(argc, argv)
int argc;
char *argv[];
{
  int i;
  
  for (i = 1; i < argc; i++) {
    char *code;
    token *next;
    itratr *iter;
    
    code = rdfile(argv[i]);
    prelex(code);

    printf("%s\n===[ tokens ]===\n", code);

    iter = lex(code);

    while ((next = itrnxt(iter)) != NULL) {
#if DEBUG
      printf("%s - [%s]\n", strtyp(next->type), next->string);
#else
      printf("%s ", next->string);
#endif
      free(next->string);
      free(next);
    }

#if DEBUG
#else
    printf("\n");
#endif

    free(code);
  }
}
