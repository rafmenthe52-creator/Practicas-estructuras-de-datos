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
