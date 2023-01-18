#include <stdio.h>
#include "lexer.h"
#include "dynmem.h"
#include "rdfile.h"
#include "bool.h"
#include "dynmem.h"
#include "preprocess.h"
#include "cross.h"
#include "iter.h"

typedef struct ppstate {
  struct ppstate *down;
  char *ptr;
  char *bgnptr;
#if DEBUG
  char *why;
#endif
} ppstate;

typedef struct macrodefs {
  char *name;
  char *replacewith;
  struct macrodefs *next;
} macrodefs;

extern char *strtok_r();

int krstrncmp(s, t, l)
char *s, *t;
int l;
{
  for (; l--; s++, t++)
    if (*s != *t)
      return(*s - *t);
  return(0);
}

int deffree(defs)
macrodefs *defs;
{
  if (defs == NULL)
    return(0);
  free(defs->name);
  free(defs->replacewith);
  deffree(defs->next);
  free(defs);
  return(0);
}

macrodefs **defadd(defs, name, replacewith)
macrodefs **defs;
char *name, *replacewith;
{
  macrodefs *new_defs = malloc(sizeof(macrodefs));
  new_defs->name = name;
  new_defs->replacewith = replacewith;
  new_defs->next = *defs;
  *defs = new_defs;
  return(defs);
}

macrodefs **defrm(defs, name)
macrodefs **defs;
char *name;
{
  if (*defs != NULL) {
    if (!krstrcmp((*defs)->name, name))
      *defs = (*defs)->next;
    (*defs)->next = *defrm(&((*defs)->next), name);
  }
  return(defs);
}

bool defhas(defs, name)
macrodefs *defs;
char *name;
{
  if (defs != NULL)
#if DEBUG
  {
    printf("has(defs, \"%s\"). defs->name == \"%s\"", name, defs->name);
#endif
    return(false);
#if DEBUG
  }
#endif
  else if (!krstrcmp(defs->name, name))
    return(true);
  else
    return(defhas(defs->next, name));
  /* TODO: tail call optimization */
}

char *defget(defs, name)
macrodefs *defs;
char *name;
{
  if (defs == NULL)
    return(NULL);
  else if (!krstrcmp(defs->name, name))
    return(defs->replacewith);
  else
    return(defget(defs->next, name));
  /* TODO: tail call optimization */
}

int dbmac(defs)
macrodefs *defs;
{
#if DEBUG
  printf("/* %x */\n", defs);
#endif
  
  if (defs == NULL)
    return(0);
  
#if DEBUG
  printf("#define %s %s\n", defs->name, defs->replacewith);
#endif
  return(dbmac(defs->next));
}

void prelex(str)
char str[];
{
  char *p = str;
  
  while (*p != '\0')
    if (*p == '\\' && *(p + 1) == '\n')
      krmemcpy(p, p + 2, krstrlen(p + 2) + 1);
    else
      p++;
  
  return;
}

itratr *preprocess(itratr *)

/*
token *preprocess(ptr, state, defs)
char *ptr[];
ppstate **state;
macrodefs **defs;
{
  token *next;

  if (defs == NULL)
    return(NULL);

  if (state == NULL)
    return(NULL);
  
  if (*state != NULL) {
    token *tok;
    ppstate *next_state;
    
    tok = preprocess(&(*state)->ptr, &((*state)->down), defs);

    #if DEBUG
    printf("(%s) [%s]\n", (*state)->why, (*state)->bgnptr);
    #endif
    
    if (tok != NULL)
      return(tok);

    free((*state)->bgnptr);
    next_state = (*state)->down;
    free(*state);
    *state = next_state;
  }
  
  next = lex(ptr);
  
  if (next == NULL) {
    return(next);
  }
  
  if (next->type == PRPROC_TOKEN) {
    if (!krstrncmp(next->string, "#include", 8)) {
      char *save;
      if (strtok_r(next->string, " \t", &save) != NULL) {
        char *filename = strtok_r(NULL, " \t", &save);
     
        if (filename[0] == '"' || filename[0] == '<') {
          char *buf;
          ppstate *old;
          
          filename[krstrlen(filename) - 1] = '\0';
          
          buf = malloc(krstrlen(filename) + 9);
          if (filename[0] == '"')
            sprintf(buf, "./input/%s", filename + 1);
          else if (filename[0] == '<')
            sprintf(buf, "./include/%s", filename + 1);
          buf[krstrlen(buf)] = '\0';
          
          old = *state;
          *state = malloc(sizeof(ppstate));
          
          (*state)->ptr = rdfile(buf);
          (*state)->down = old;
          (*state)->bgnptr = (*state)->ptr;
          #if DEBUG
          (*state)->why = "#include expansion";
          #endif
          
          free(buf);
          
          return(preprocess(ptr, state, defs));
        }
      }
    } else if (!krstrncmp(next->string, "#define", 7)) {
      char *save;
      if (strtok_r(next->string, " \t", &save) != NULL) {
        char *name, *cpyname, *replacewith, *cpyreplacewith;
        name = strtok_r(NULL, " \t", &save);
        cpyname = falloc(name);
        
        replacewith = strtok_r(NULL, "", &save);
        if (replacewith == NULL)
          cpyreplacewith = falloc("");
        else
          cpyreplacewith = falloc(replacewith);
     
        defadd(defs, cpyname, cpyreplacewith);
      }
      return(preprocess(ptr, state, defs));
    } else if (!krstrncmp(next->string, "#ifdef", 6)) {
      char *save;
      if (strtok_r(next->string, " \t", &save) != NULL) {
        char *name, *cpyname, *replacewith, *cpyreplacewith;
        variable = strtok_r(NULL, "", &save);
        if (defhas(*defs, variable)) {
          
        }
      }
      return(preprocess(ptr, state, defs));
    }
    
    free(next->string);
    free(next);
    return preprocess(ptr, state, defs);
  } else if (next->type == IDENTF_TOKEN) {
    if (defhas(*defs, next->string)) {
      char *content;
      ppstate *old;
      content = falloc(defget(*defs, next->string));
      
      old = *state;
      *state = malloc(sizeof(ppstate));
      
      (*state)->ptr = content;
      (*state)->down = old;
      (*state)->bgnptr = (*state)->ptr;
      #if DEBUG
      (*state)->why = "#define expansion";
      #endif
          
      return(preprocess(ptr, state, defs));
    } else {
      return next;
    }
  } else {
    return next;
  }
}
*/
