#include "cross.h"
#include "iter.h"

#ifndef LEXER
  #define LEXER
  
  #if C89
    
    typedef enum tokentype {
  #define X(T, V) T
  #define SEP ,
  #include "tokens.def"
    } tokentype;
    
  #else
    
  #define X(T, V) static int T = V;
  #include "tokens.def"
    typedef int tokentype;
    
  #endif
  
  typedef struct token {
    tokentype type;
    char *string;
  } token;
  
  itratr *lex();
#endif
