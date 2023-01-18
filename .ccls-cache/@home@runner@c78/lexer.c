#include <stdio.h>
#include "lexer.h"
#include "dynmem.h"

extern size_t strlen();

token *next_token(res, bgnptr, ptr)
token *res;
char *bgnptr, **ptr;
{
  /* and now for the tricky bit */
general:
  switch (**ptr) {
  case '\0':
    return(NULL);
  case ' ':
  case '\t':
  case '\r':
  case '\n':
    (*ptr)++;
    bgnptr++;
    goto general;
  case '(':
    (*ptr)++;
    res->type = LPAREN_TOKEN;
    res->string = falloc("(");
    return(res);
  case ')':
    (*ptr)++;
    res->type = RPAREN_TOKEN;
    res->string = falloc(")");
    return(res);
  case '{':
    (*ptr)++;
    res->type = LCURLY_TOKEN;
    res->string = falloc("{");
    return(res);
  case '}':
    (*ptr)++;
    res->type = RCURLY_TOKEN;
    res->string = falloc("}");
    return(res);
  case '[':
    (*ptr)++;
    res->type = LBRACK_TOKEN;
    res->string = falloc("[");
    return(res);
  case ']':
    (*ptr)++;
    res->type = RBRACK_TOKEN;
    res->string = falloc("]");
    return(res);
  case ';':
    (*ptr)++;
    res->type = SMICLN_TOKEN;
    res->string = falloc(";");
    return(res);
  case '+':
    (*ptr)++;
    goto _2operator;
  case '*':
    (*ptr)++;
    goto _3operator;
  case '-':
    (*ptr)++;
    goto _4operator;
  case '=':
    (*ptr)++;
    goto _5operator;
  case '<':
    (*ptr)++;
    goto _6operator;
  case '>':
    (*ptr)++;
    goto _7operator;
  case ',':
    (*ptr)++;
    res->type = COMMA_TOKEN;
    res->string = falloc(",");
    return(res);
  case '"':
    (*ptr)++;
    goto d1string;
  case '\'':
    (*ptr)++;
    goto s1string;
  case '!':
    (*ptr)++;
    goto _8operator;
  case '&':
    (*ptr)++;
    goto _9operator;
  case '|':
    (*ptr)++;
    goto _10operator;
  case ':':
    (*ptr)++;
    res->type = COLON_TOKEN;
    res->string = falloc(":");
    return(res);
  case '#':
    (*ptr)++;
    goto _preprocessor;
  case '/':
    (*ptr)++;
    goto slash;
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z':
  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
  case 'G':
  case 'H':
  case 'I':
  case 'J':
  case 'K':
  case 'L':
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  case 'R':
  case 'S':
  case 'T':
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z':
  case '_':
    ++(*ptr);
    goto identifier;
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    ++(*ptr);
    goto number;
  default:
    return(NULL);
  }
  goto general;
slash:
  switch (**ptr) {
  case '\0':
    return(NULL);
  case '*':
    (*ptr)++;
    goto mcomment;
  case '=':
    (*ptr)++;
    res->type = IDIV_TOKEN;
    res->string = falloc("/=");
    return(res);
  default:
    (*ptr)++;
    res->type = DIV_TOKEN;
    res->string = falloc("/");
    return(res);
  }
mcomment:
  switch (**ptr) {
  case '\0':
    return(NULL);
  case '*':
    (*ptr)++;
    goto smcomment;
  default:
    (*ptr)++;
    goto mcomment;
  }
smcomment:
  switch (**ptr) {
  case '\0':
    return(NULL);
  case '/':
    (*ptr)++;
    bgnptr = *ptr;
    goto general;
  default:
    (*ptr)++;
    goto mcomment;
  }
identifier:
  switch (**ptr) {
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z':
  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
  case 'G':
  case 'H':
  case 'I':
  case 'J':
  case 'K':
  case 'L':
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  case 'R':
  case 'S':
  case 'T':
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '_':
    (*ptr)++;
    goto identifier;
  default: {
    size_t len = *ptr - bgnptr;
    char *string;
    string = malloc(len);
    krmemcpy(string, bgnptr, len);
    res->string = string;
    
    if (/* types */
        !krstrcmp("char", string)
    ||  !krstrcmp("short", string)
    ||  !krstrcmp("int", string)
    ||  !krstrcmp("long", string)
    ||  !krstrcmp("unsigned", string)
    ||  !krstrcmp("float", string)
    ||  !krstrcmp("double", string)
    ||  !krstrcmp("typedef", string)
    ||  !krstrcmp("struct", string)
    ||  !krstrcmp("union", string)
        /* scoping */
    ||  !krstrcmp("auto", string)
    ||  !krstrcmp("static", string)
    ||  !krstrcmp("extern", string)
    ||  !krstrcmp("register", string)
        /* control flow */
    ||  !krstrcmp("if", string)
    ||  !krstrcmp("else", string)
    ||  !krstrcmp("while", string)
    ||  !krstrcmp("do", string)
    ||  !krstrcmp("for", string)
    ||  !krstrcmp("switch", string)
    ||  !krstrcmp("case", string)
    ||  !krstrcmp("default", string)
    ||  !krstrcmp("return", string)) {
      res->type = KEYWRD_TOKEN;
    } else {
      res->type = IDENTF_TOKEN;
    }
    return(res);
  }
  }
  goto identifier;
_2operator:
  switch (**ptr) {
  case '+':
    (*ptr)++;
    res->type = INCRMN_TOKEN;
    res->string = falloc("++");
    return(res);
  default:
    (*ptr)++;
    res->type = PLUS_TOKEN;
    res->string = falloc("+");
    return(res);
  }
_3operator:
  switch (**ptr) {
  default:
    res->type = ASTRSK_TOKEN;
    res->string = falloc("*");
    return(res);
  }
_4operator:
  switch (**ptr) {
  case '-':
    (*ptr)++;
    res->type = DECRMN_TOKEN;
    res->string = falloc("--");
    return(res);
  case '>':
    (*ptr)++;
    res->type = DERACS_TOKEN;
    res->string = falloc("->");
    return(res);
  default:
    res->type = MINUS_TOKEN;
    res->string = falloc("-");
    return(res);
  }
_5operator:
  switch (**ptr) {
  case '=':
    (*ptr)++;
    res->type = DEQUAL_TOKEN;
    res->string = falloc("==");
    return(res);
  default:
    res->type = ASSIGN_TOKEN;
    res->string = falloc("=");
    return(res);
  }
_6operator:
  switch (**ptr) {
  case '=':
    (*ptr)++;
    res->type = LESSEQ_TOKEN;
    res->string = falloc("<=");
    return(res);
  default:
    res->type = LESSTH_TOKEN;
    res->string = falloc("<");
    return(res);
  }
_7operator:
  switch (**ptr) {
  case '=':
    (*ptr)++;
    res->type = GRTREQ_TOKEN;
    res->string = ">=";
    return(res);
  default:
    res->type = GRTRTH_TOKEN;
    res->string = ">";
    return(res);
  }
d1string:
  switch (**ptr) {
  case '\0':
    return(NULL);
  case '"': {
    size_t len;
    char *string;
    (*ptr)++;
    len = *ptr - bgnptr;
    string = malloc(len);
    krmemcpy(string, bgnptr, len);
    res->string = string;
    res->type = DSTRING_TOKEN;
    return(res);
  }
  default:
    (*ptr)++;
    goto d1string;
  }
s1string:
  switch (**ptr) {
  case '\0':
    return(NULL);
  case '\'':
    return(NULL);
  case '\\':
    (*ptr) += 2;
    goto s2string;
  default:
    (*ptr)++;
    goto s2string;
  }
s2string:
  switch (**ptr) {
  case '\'': {
    size_t len;
    char *string;
    (*ptr)++;
    len = *ptr - bgnptr;
    string = malloc(len);
    krmemcpy(string, bgnptr, len);
    res->string = string;
    res->type = SSTRING_TOKEN;
    return(res);
  }
  default:
    return(NULL);
  }
_8operator:
  switch (**ptr) {
  case '=':
    (*ptr)++;
    res->type = NOTEQU_TOKEN;
    res->string = "!=";
    return(res);
  default:
    res->type = NOT_TOKEN;
    res->string = "!";
    return(res);
  }
_9operator:
  switch (**ptr) {
  case '&':
    (*ptr)++;
    res->type = LOGAND_TOKEN;
    res->string = "&&";
    return(res);
  default:
    res->type = AMPRSD_TOKEN;
    res->string = "&";
    return(res);
  }
_10operator:
  switch (**ptr) {
  case '|':
    (*ptr)++;
    res->type = LOGOR_TOKEN;
    res->string = "||";
    return(res);
  case '=':
    (*ptr)++;
    res->type = IOR_TOKEN;
    res->string = "|=";
    return(res);
  default:
    res->type = OR_TOKEN;
    res->string = "|";
    return(res);
  }
_preprocessor:
  /* #define  */
  /* #else    */
  /* #endif   */
  /* #if      */
  /* #ifdef   */
  /* #ifndef  */
  /* #include */
  /* #line    */
  /* #undef   */
  switch (**ptr) {
  case '\0':
    return(NULL);
  case 'd':
    (*ptr)++;
    goto d_preprocessor;
  case 'e':
    (*ptr)++;
    goto e_preprocessor;
  case 'i':
    (*ptr)++;
    goto i_preprocessor;
  case 'l':
    (*ptr)++;
    goto l_preprocessor;
  case 'u':
    (*ptr)++;
    goto u_preprocessor;
  default:
    return(NULL);
  }
d_preprocessor:
  /* #define  */
  switch (**ptr) {
  case 'e':
    (*ptr)++;
    goto de_preprocessor;
  default:
    return(NULL);
  }
de_preprocessor:
  /* #define  */
  switch (**ptr) {
  case 'f':
    (*ptr)++;
    goto def_preprocessor;
  default:
    return(NULL);
  }
def_preprocessor:
  /* #define  */
  switch (**ptr) {
  case 'i':
    (*ptr)++;
    goto defi_preprocessor;
  default:
    return(NULL);
  }
defi_preprocessor:
  /* #define  */
  switch (**ptr) {
  case 'n':
    (*ptr)++;
    goto defin_preprocessor;
  default:
    return(NULL);
  }
defin_preprocessor:
  /* #define  */
  switch (**ptr) {
  case 'e':
    (*ptr)++;
    goto _define_preprocessor;
  default:
    return(NULL);
  }
e_preprocessor:
  /* #else    */
  /* #endif   */
  switch (**ptr) {
  case 'l':
    (*ptr)++;
    goto el_preprocessor;
  case 'n':
    (*ptr)++;
    goto en_preprocessor;
  default:
    return(NULL);
  }
el_preprocessor:
  /* #else    */
  switch (**ptr) {
  case 's':
    (*ptr)++;
    goto els_preprocessor;
  default:
    return(NULL);
  }
els_preprocessor:
  /* #else    */
  switch (**ptr) {
  case 'e':
    (*ptr)++;
    goto _else_preprocessor;
  default:
    return(NULL);
  }
en_preprocessor:
  /* #endif   */
  switch (**ptr) {
  case '\0':
    return(NULL);
  case 'd':
    (*ptr)++;
    goto end_preprocessor;
  default:
    return(NULL);
  }
end_preprocessor:
  /* #endif   */
  switch (**ptr) {
  case 'i':
    (*ptr)++;
    goto endi_preprocessor;
  default:
    return(NULL);
  }
endi_preprocessor:
  /* #endif   */
  switch (**ptr) {
  case 'f':
    (*ptr)++;
    goto _endif_preprocessor;
  default:
    return(NULL);
  }
i_preprocessor:
  /* #if      */
  /* #ifdef   */
  /* #ifndef  */
  /* #include */
  switch (**ptr) {
  case 'f':
    (*ptr)++;
    goto if_preprocessor;
  case 'n':
    (*ptr)++;
    goto in_preprocessor;
  default:
    return(NULL);
  }
if_preprocessor:
  /* #if      */
  /* #ifdef   */
  /* #ifndef  */
  switch (**ptr) {
  case 'd':
    (*ptr)++;
    goto ifd_preprocessor;
  case 'n':
    (*ptr)++;
    goto ifn_preprocessor;
  default:
    goto _if_preprocessor;
  }
ifd_preprocessor:
  /* #ifdef   */
  switch (**ptr) {
  case 'e':
    (*ptr)++;
    goto ifde_preprocessor;
  default:
    return(NULL);
  }
ifde_preprocessor:
  /* #ifdef   */
  switch (**ptr) {
  case 'f':
    (*ptr)++;
    goto _ifdef_preprocessor;
  default:
    return(NULL);
  }
ifn_preprocessor:
  /* #ifndef  */
  switch (**ptr) {
  case 'd':
    (*ptr)++;
    goto ifnd_preprocessor;
  default:
    return(NULL);
  }
ifnd_preprocessor:
  /* #ifndef  */
  switch (**ptr) {
  case 'e':
    (*ptr)++;
    goto ifnde_preprocessor;
  default:
    return(NULL);
  }
ifnde_preprocessor:
  /* #ifndef  */
  switch (**ptr) {
  case 'f':
    (*ptr)++;
    goto _ifndef_preprocessor;
  default:
    return(NULL);
  }
in_preprocessor:
  /* #include */
  switch (**ptr) {
  case 'c':
    (*ptr)++;
    goto inc_preprocessor;
  default:
    return(NULL);
  }
inc_preprocessor:
  /* #include */
  switch (**ptr) {
  case 'l':
    (*ptr)++;
    goto incl_preprocessor;
  default:
    return(NULL);
  }
incl_preprocessor:
  /* #include */
  switch (**ptr) {
  case 'u':
    (*ptr)++;
    goto inclu_preprocessor;
  default:
    return(NULL);
  }
inclu_preprocessor:
  /* #include */
  switch (**ptr) {
  case 'd':
    (*ptr)++;
    goto includ_preprocessor;
  default:
    return(NULL);
  }
includ_preprocessor:
  /* #include */
  switch (**ptr) {
  case 'e':
    (*ptr)++;
    goto _include_preprocessor;
  default:
    return(NULL);
  }
l_preprocessor:
  /* #line    */
  switch (**ptr) {
  case 'i':
    (*ptr)++;
    goto li_preprocessor;
  default:
    return(NULL);
  }
li_preprocessor:
  /* #line    */
  switch (**ptr) {
  case 'n':
    (*ptr)++;
    goto lin_preprocessor;
  default:
    return(NULL);
  }
lin_preprocessor:
  /* #line    */
  switch (**ptr) {
  case 'e':
    (*ptr)++;
    goto _line_preprocessor;
  default:
    return(NULL);
  }
u_preprocessor:
  /* #undef   */
  switch (**ptr) {
  case 'n':
    (*ptr)++;
    goto un_preprocessor;
  default:
    return(NULL);
  }
un_preprocessor:
  /* #undef   */
  switch (**ptr) {
  case 'd':
    (*ptr)++;
    goto und_preprocessor;
  default:
    return(NULL);
  }
und_preprocessor:
  /* #undef   */
  switch (**ptr) {
  case 'e':
    (*ptr)++;
    goto unde_preprocessor;
  default:
    return(NULL);
  }
unde_preprocessor:
  /* #undef   */
  switch (**ptr) {
  case 'e':
    (*ptr)++;
    goto _undef_preprocessor;
  default:
    return(NULL);
  }
_define_preprocessor:
_else_preprocessor:
_endif_preprocessor:
_if_preprocessor:
_ifdef_preprocessor:
_ifndef_preprocessor:
_include_preprocessor:
_line_preprocessor:
_undef_preprocessor:
_gen_preprocessor:
  switch (**ptr) {
  case '\0':
  case '\n': {
    size_t len = *ptr - bgnptr;
    char *string;
    string = malloc(len);
    krmemcpy(string, bgnptr, len);
    res->string = string;
    res->type = PRPROC_TOKEN;
    return(res);
  }
  case '\\': {
    (*ptr) += 2;
    goto _gen_preprocessor;
  }
  default:
    (*ptr)++;
    goto _gen_preprocessor;
  }
number:
  switch (**ptr) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    (*ptr)++;
    goto number;
  default: {
    size_t len = *ptr - bgnptr;
    char *string;
    string = malloc(len);
    krmemcpy(string, bgnptr, len);
    res->string = string;
    res->type = NUMBER_TOKEN;
    return(res);
  }
  }
  goto number;
}

void *lexnxt(ptrv)
void **ptrv;
{
  char **ptr = (char **) ptrv;
  
  if (ptr == NULL) {
    printf("lexer invocation error\n");
    return(NULL);
  } else if (*ptr == NULL || **ptr == '\0') {
    return(NULL);
  } else {
    token *res;
    char *bgnptr = *ptr;
    
    res = malloc(sizeof(token));
    return next_token(res, bgnptr, ptr);
  }
}

itratr *lex(str)
char str[];
{
  itratr *res;
  res = malloc(sizeof(itratr));
  res->current = malloc(sizeof(int));
  res->state = malloc(strlen(str));
  krmemcpy(res->state, str, strlen(str));
  res->next = lexnxt;
  return(res);
}
