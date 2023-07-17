#include <stdio.h>
#include "lexer.h"

#define YES 1
#define NO 0

int main(argc, argv)
  int argc;
  char *argv[];
{
  struct lexer l;
  struct token t;
  
  if (argc <= 1)
    return -1;
  
  l.has_previous = NO;
  if ((l.f = fopen(argv[1], "r"))) {
    while (next_lexer(&t, &l)) {
      if (t.type == ERROR_TOKEN) {
        return -1;
      } else if (t.type == IDENT_TOKEN) {
        printf("identifier: %s\n", t.data.ident);
      } else if (t.type == NUMBER_TOKEN) {
        printf("number: %u\n", t.data.ui);
      }
    }
    fclose(l.f);
    l.f = (FILE *) 0;
  }
  return 0;
}
