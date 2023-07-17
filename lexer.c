#include <stdio.h>
#include "lexer.h"

#define YES 1
#define NO 0

isspace(c) {
  return c == ' '  ||
         c == '\t' ||
         c == '\f' ||
         c == '\r' ||
         c == '\n';
}

isdigit(c) {
  return c >= '0' && c <= '9';
}

isalpha(c) {
  return (c >= 'A' && c <= 'Z') ||
         (c >= 'a' && c <= 'z');
}

isalnum(c) {
  return (c >= '0' && c <= '9') ||
         (c >= 'A' && c <= 'Z') ||
         (c >= 'a' && c <= 'z');
}

next_lexer(tok, state)
  struct token *tok;
  struct lexer *state;
{
  register int c;
  
  if (!state)
    goto fail;
  
  while (isspace(c = fgetc(state->f)))
    ;
  
  if (state->has_previous) {
    state->has_previous = NO;
    *tok = state->previous;
  } else if (c == EOF) {
    return NO;
  } if (isdigit(c)) {
    register unsigned int num = 0;
    tok->type = NUMBER_TOKEN;
    
    do {
      num = (num * 10) + (c - '0');
      c = fgetc(state->f);
    } while (isdigit(c));
    
    tok->data.ui = num;
  } else if (isalpha(c) || c == '_') {
    register unsigned int i = 0;
    tok->type = IDENT_TOKEN;
    
    do {
      if (i < sizeof(tok->data.ident) - 1)
        tok->data.ident[i++] = c;
      c = fgetc(state->f);
    } while (isalnum(c));
    
    tok->data.ident[i] = '\0';
  }
  
  return YES;

fail:
  tok->type = ERROR_TOKEN;
  return YES;
}
