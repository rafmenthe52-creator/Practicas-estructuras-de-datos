#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define INIT_CAPACITY 2 // init stack capacity
#define FCT_CAPACITY 2 // multiply the stack capacity

struct _Stack {
  void **item; /*!<Static array of elements*/
  int top; /*!<index of the top element in the stack*/
  int capacity; /*!<xcapacity of the stack*/
};

/*Private functions*/

Status stack_expand(Stack *sin){
  Stack *stack;
  
  if(!sin){
    return ERROR;
  }
  
  stack=(Stack*)realloc(sin, stack->capacity*FCT_CAPACITY*sizeof(Stack));

  return OK;
}

/*Public functions*/

Stack* stack_init (){
  Stack *stack;

  stack=(Stack*)malloc(INIT_CAPACITY*sizeof(Stack));

  return stack;
}


void stack_free (Stack *s){
  int i;

  for(i=0; i<s->capacity; i++){
    free(s->item[i]);
  }

  free(s);
}

Status stack_push (Stack *sin, const void *ele){
  Stack *s;
  
  if(!sin || !ele){
    return ERROR;
  }

  if(sin->top == sin->capacity){
    if(stack_expand(sin)==ERROR){
      return ERROR;
    }
  }

  s = (Stack*)realloc(sin, sin->top*sizeof(s));
  if(!s){
    return ERROR;
  }

  s->item[s->top] = (void *)ele;

  s->top++;

  return OK;
}

void * stack_pop (Stack *s){
  if(!s){
    return NULL;
  }

  s->top--;

  return s->item[s->top+1];
}

void * stack_top (const Stack *s){
  if(!s){
    return NULL;
  }
  
  return s->item[s->top];
}

Bool stack_isEmpty (const Stack *s){
  if(!s){
    return TRUE;
  }

  if(s->top==0){
    return TRUE;
  }

  return FALSE;
}

size_t stack_size (const Stack *s){
  if(!s){
    return -1;
  }

  return s->top;
}

int stack_print(FILE* fp, const Stack *s,  P_stack_ele_print f){
  int i, n;
  
  if(!s || !fp){
    return -1;
  }

  for(i=0; i<s->top; i++){
    n+=f(fp, s->item[i]);
  }

  return n;
}
