#include "list.h"
#include<stdio.h>
#include<stdlib.h>

#define N 10

typedef struct pair_{
  int x;
  int y;
} Pair;


char* pair2str(void *data);
int pair_destroy(void *data);
Pair *newPair(int x, int y);

/*
  Create a list of Pairs and play around with it

 */
int main(int argc, char **argv){
  int i,j;
  List *list;
  ListElmt *e;
  Pair a;
  Pair *ap = &a;
  list = (List *) malloc(sizeof(List));
  list_init(list,pair_destroy,NULL,pair2str);

  Pair *p = newPair(1,1);
  /* insert at head of list */
  list_ins_next(list,NULL,p);
  list_print(list);

  e = list->head;
  for (i=1;i<N;++i){
    Pair *p = newPair(i/3, i%3);
    list_ins_next(list,e,p);
    e = e->next;
    list_print(list);
  }

  /* remove one of the Pair elements */
  list_rem_next(list,NULL,(const void **) &ap);
  list_print(list);

  /* now let's try O[n] interface */
  list_add(list, 3, newPair(-1,-1));
  list_print(list);
  ap = (Pair *) list_element_at(list,3);
  printf("value of element 3: %s\n", pair2str(ap)); 
  list_destroy(list);
  return 0;

}
char* pair2str(void *data){
  static char str[10];
  Pair *p = (Pair *) data;
  sprintf(str, "[%d,%d]", p->x, p->y);
  return str;
}

int pair_destroy(void *data){
  Pair *p = (Pair *) data;
  free(p);
  return 0;
}

Pair *newPair(int x, int y){
  Pair *p = malloc(sizeof(Pair));
  p->x = x; p->y = y;
  return p;
}

