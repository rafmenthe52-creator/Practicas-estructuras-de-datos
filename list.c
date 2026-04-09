#include "list.h"
#include <stdlib.h>

struct _Node{
  void *info;
  struct _Node *next;
};

typedef struct _Node Node;

struct _List{
  Node *first;  /*!< First node of that list*/
  Node *last;   /*!< Lasr node of that list*/
  int size;
};

/* Private functions*/

Node * node_new () {
  Node *pn = NULL;

  pn = (Node *) malloc(sizeof(Node));

  if (pn == NULL) {
    return NULL;
  }
  
  pn ->info = NULL;
  pn ->next = NULL;
  return pn;
}


/* Public funtions*/

List *list_new(){
  List *list;

  list = (List*)malloc(sizeof(List));

  if(!list) return NULL;

  list->first = node_new();
  list->last = node_new();

  if(!list->first||!list->last){
    free(list);
    return NULL;
  }

  list->first->next=list->last;

  list->size = INIT_VALUE;

  return list;
}


Bool list_isEmpty(const List *pl){
  if(!pl) return TRUE;

  if(pl->size == 0) return TRUE;

  return FALSE;
}


Status list_pushFront(List *pl, const void *e){
  Node *nodeNew = node_new();

  if(!pl || !e || !nodeNew) return ERROR;

  nodeNew->info = (void *)e;
  nodeNew->next = pl->first;
  pl->first = nodeNew;

  if(pl->size==INIT_VALUE){
    pl->last = nodeNew;
  }

  pl->size++;

  return OK;
}

Status list_pushBack(List *pl, const void *e){
  Node *nodeNew = node_new();
  
  if(!pl||!e||!nodeNew) return ERROR;

  nodeNew->info = (void*)e;

  if(list_isEmpty(pl) == TRUE){
    pl->first = nodeNew;
  } else {
    pl->last->next = nodeNew;
  }

  pl->last = nodeNew;
  pl->size++;

  return OK;
}

void *list_popFront(List *pl){
  void *e;
  Node *nodeFront;

  if(!pl || list_isEmpty(pl)==TRUE ) return NULL;

  nodeFront = pl->first;
  e = nodeFront->info;

  pl->first = nodeFront->next;

  if(pl->first==NULL){
    pl->last = NULL;
  }

  free(nodeFront);
  pl->size--;

  return e;
}

void *list_popBack(List *pl){
  void *e;
  Node *pn;

  if(!pl|| list_isEmpty(pl)==TRUE) return NULL;

  

  /* In the case that the list only has one element */
  if (pl ->first ->next == NULL) {
    e = pl ->first ->info;
    pl->last = NULL;
    free (pl ->first);
    pl->first = NULL;
    return e;
  } 

  pn = pl->first;

  /* Find the pointer whose second next pointer is NULL. In other words the one before last*/
  while (pn->next->next!=NULL){
    pn=pn->next;
  }

  e = pl->last->info;

  free(pl->last);

  pn->next = NULL;


  pl->last = pn;
  pl->size--;

  return e;
}

void *list_getFront(List *pl){
  if(!pl || list_isEmpty(pl)==TRUE) return NULL;

  return pl->first->info;
}

void *list_getBack(List *pl){
  if(!pl || list_isEmpty(pl)==TRUE) return NULL;

  return pl->last->info;
}

void list_free(List *pl){
  Node *nCurrent, *nNext;
  
  if(!pl) return;

  if(list_isEmpty(pl) == FALSE){
    nCurrent = pl->first;

    while(nCurrent != NULL){
      nNext = nCurrent->next;
      free(nCurrent);
      nCurrent = nNext;
    }
  }

  free(pl);

  return;
}

int list_size(const List *pl){
  if(!pl) return INVALID_INT;

  return pl->size;
}

int list_print(FILE *fp, const List *pl, p_list_ele_print f){
  int count = 0;
  Node *nCurrent;

  if (!fp || !pl || !f) {
    return INVALID_INT;
  }

  if (list_isEmpty(pl) == TRUE) return INVALID_INT;

  nCurrent = pl->first;

  while(nCurrent != NULL){
    count += f(fp, nCurrent->info);
    if (count < 0) return INVALID_INT;
    
    count += fprintf(stdout, "\n");
    if (count < 0) return INVALID_INT;
    
    nCurrent = nCurrent->next;
  }

  return count;
}
