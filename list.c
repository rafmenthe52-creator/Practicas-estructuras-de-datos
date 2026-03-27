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

/**
 * @brief Public function that checks if a List is Full.
 *
 * Note that the return value is FALSE for a NULL List.
 *
 * @param pl Pointer to the List.
 *
 * @return boolean value TRUE if the list is full, boolean value FALSE
 * otherwise.
 */
Bool list_isFull(const List *pl){

}

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

  return list;
}


Bool list_isEmpty(const List *pl){
  if(!pl) return TRUE;

  if(pl->first->next==pl->last){
    return TRUE;
  }

  return FALSE;
}


Status list_pushFront(List *pl, const void *e){
  Node *nodeCopy = node_new();
  
  if(!pl||!e||!list_isFull(pl)==TRUE||!nodeCopy) return ERROR;

  nodeCopy=pl->first;

  pl->first->info = e;
  pl->first->next = nodeCopy;

  return OK;
}

Status list_pushBack(List *pl, const void *e){
  Node *nodeNew = node_new();
  
  if(!pl||!e||list_isFull==TRUE||!node_new) return ERROR;

  nodeNew->info = e;

  pl->last->next = nodeNew;

  pl->last = nodeNew;

  return OK;
}

void *list_popFront(List *pl){
  void *e;

  if(!pl || list_isEmpty(pl)==TRUE ) return NULL;

  e = pl->first->info;

  free(pl->first);
  
  return e;
}

void *list_popBack(List *pl){
  void *e;
  Node *pn;

  if(!pl|| list_isEmpty(pl)==TRUE) return NULL;

  pn = pl->first;

  /* In the case that the list only has one element */
  if (pl ->first ->next == NULL) {
    e = pl ->first ->info;
    free (( void *)pl ->first);
    pl ->first = NULL;
    return e;
  } 

  /* Find the pointer whose second next pointer is NULL. In other words the one before last*/
  while (pn->next->next!=NULL){
    pn=pn->next;
  }

  e = pl->last->info;
  
  free(pl->last);

  pn->next = NULL;

  pl->last = pn;

  return e;
}
