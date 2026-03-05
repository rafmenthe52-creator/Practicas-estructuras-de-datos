/**
* @brief: Merges two stacks
*
* @param sin1, first input stack
* @param sin2, second input stack
* @param sout, result stack
* @return The function returns OK or ERROR
**/

#include <stdio.h>
#include <stdlib.h>

#include "music.h"
#include "stack.h"
#include "mergestack.h"

Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, P_mergestack_cmp f){
  if(!sin1||!sin2|!sout){
    return ERROR;
  }

  while(stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE){
    if(f(stack_top(sin1), stack_top(sin2))<=0){
      /*first is larger*/
      stack_push(sout, stack_pop(sin1));
    }else if(f(stack_top(sin1), stack_top(sin2))>=0){
      /*Second is larger*/
      stack_push(sout, stack_pop(sin2));
    }else{
      /*They are equal*/
      stack_push(sout, stack_pop(sin2));
    }
  }
  if(stack_isEmpty(sin1)){
    while (stack_isEmpty(sin2)==FALSE){
      stack_push(sout, stack_pop(sin2));
    }
  }else{
    while (stack_isEmpty(sin1)==FALSE){
      stack_push(sout, stack_pop(sin1));
    }
  }

  return OK;
}