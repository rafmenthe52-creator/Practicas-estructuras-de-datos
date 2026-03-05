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

Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, ){
  while(stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE){
    if(music_getDuration(stack_top(sin1))>music_getDuration(stack_top(sin2))){
      stack_push(sout, stack_pop(sin1));
    }else{
      stack_push(sout, stack_pop(sin2));
    }
  }
}