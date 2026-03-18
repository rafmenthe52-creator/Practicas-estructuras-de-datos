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

Stack* stack_expand(Stack *sin){
  void **new_item;
  
  if(!sin) return NULL;
  
  new_item = (void**)realloc(sin->item, 
                              sin->capacity * FCT_CAPACITY * sizeof(void*));
  if(!new_item) return NULL;

  sin->item = new_item;
  sin->capacity = sin->capacity * FCT_CAPACITY;

  return sin;
}

Stack* stack_init (){
  Stack *stack;

  stack = (Stack*)malloc(sizeof(Stack));
  if(!stack) return NULL;
  
  stack->item = (void**)malloc(INIT_CAPACITY * sizeof(void*));
  if(!stack->item){
    free(stack);
    return NULL;
  }

  stack->capacity = INIT_CAPACITY;
  stack->top = 0;

  return stack;
}


void stack_free (Stack *s){
  if(!s) return;
  free(s->item);  
  free(s);        
}

Status stack_push (Stack *sin, const void *ele){
  if(!sin || !ele) return ERROR;

  if(sin->top == sin->capacity){
    if(!stack_expand(sin)){
      return ERROR;
    }
  }

  sin->item[sin->top] = (void *)ele;
  sin->top++;

  return OK;
}

void * stack_pop (Stack *s){
  if(!s || s->top == 0){
    return NULL;
  }

  s->top--;

  return s->item[s->top];
}

void * stack_top (const Stack *s){
  if(!s || s->top == 0){
    return NULL;
  }
  
  return s->item[s->top - 1];
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
  int i, n=0;
  
  if(!s || !fp){
    return -1;
  }

  for(i=0; i<s->top; i++){
    n+=f(fp, s->item[i]);
  }

  return n;
}
