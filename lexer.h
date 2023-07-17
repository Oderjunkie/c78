#ifndef LEXER
#define LEXER
#include <stdio.h>

struct token {
  #define ERROR_TOKEN 0
  #define IDENT_TOKEN 1
  #define NUMBER_TOKEN 2
  #define STRING_TOKEN 3
  int type;
  union {
    unsigned int ui;
    char *str;
    char ident[7];
  } data;
};

struct lexer {
  FILE *f;
  int has_previous;
  struct token previous;
};

int next_lexer();
#endif
