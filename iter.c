#include "iter.h"
#include "dynmem.h"

void *itrnxt(iter)
itratr *iter;
{
  if (iter->current == NULL)
    return(iter);
  iter->current = (iter->next)(&(iter->state));
  return(iter->current);
}

void itrfre(iter)
itratr *iter;
{
  if (iter->state != NULL)
    free(iter->state);
  if (iter->current != NULL)
    free(iter->current);
  free(iter);
}

struct rngstt {
  int lwrbnd;
  int uprbnd;
};

void *rngnxt(state)
struct rngstt **state;
{
  if ((*state)->lwrbnd < (*state)->uprbnd) {
    (*state)->lwrbnd++;
    return(&((*state)->lwrbnd));
  }
  return(NULL);
}

itratr *range(lwrbnd, uprbnd)
int lwrbnd, uprbnd;
{
  itratr *res;
  res = malloc(sizeof(itratr));
  res->current = malloc(sizeof(int));
  res->state = malloc(sizeof(struct rngstt));
  ((struct rngstt *) res->state)->lwrbnd = lwrbnd - 1;
  ((struct rngstt *) res->state)->uprbnd = uprbnd;
  res->next = rngnxt;
  return(res);
}
