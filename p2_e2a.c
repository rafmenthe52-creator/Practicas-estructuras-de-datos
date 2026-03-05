#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "types.h"
#include "music.h"
#include "radio.h"
#include "stack.h"

Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout){
  if(!sin1||!sin2|!sout){
    return ERROR;
  }

  while(stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE){
    if(music_getDuration(stack_top(sin1))>music_getDuration(stack_top(sin2))){
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

void exit_execution(Radio* radio, Music** list, Stack* s, FILE *f) {
  free(list);
  radio_free(radio);
  stack_free(s);
  fclose(f);

  return;
}

int main(int argc, char** argv){
  FILE *f1, *f2;
	Radio *r1, *r2;
	Stack *s1, *s2, *s3;
	Music **list1, **list2;
	int i, mReturn;

	if (argc != 3) {
		return -1;
	}

	f1 = fopen(argv[1], "r");
	if (f1 == NULL) {
		fprintf(stderr, "Error al leer el fichero de texto 1");
		return -1;
	} 

  f2 = fopen(argv[2], "r");
	if (f2 == NULL) {
		fprintf(stderr, "Error al leer el fichero de texto 2");
		return -1;
	} 

  /*Initialize first stack*/

  r1 = radio_init();

	if (radio_readFromFile(f1, r1) == ERROR) {
		return -1;
	}

	s1 = stack_init();

	list1 = radio_getMusicList(r1);

	for (i = 0; i < radio_getNumberOfMusic(r1); i++) {
		stack_push(s1, list1[i]);
	}

  

  /*Initialize second stack*/

  r2 = radio_init();

	if (radio_readFromFile(f2, r2) == ERROR) {
		return -1;
	}

	s2 = stack_init();

	list2 = radio_getMusicList(r2);

	for (i = 0; i < radio_getNumberOfMusic(r2); i++) {
		stack_push(s2, list2[i]);
	}


  /*Print all the playlist*/
  fprintf(stdout, "playlist 1:");
  stack_print(stdout, s1, music_plain_print);
  fprintf(stdout, "\nplaylist 2:");
  stack_print(stdout, s2, music_plain_print);

  mergeStacks(s1, s2, s3);

  fprintf(stdout, "playlist combined:");
  stack_print(stdout, s3, music_plain_print);

  exit_execution(r1, list1, s1, f1);
  exit_execution(r2, list2, s2, f2);

  stack_free(s3);

  return 0;
}