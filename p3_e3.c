#include <stdio.h>
#include "list.h"
#include "music.h"
#include "file_utils.h"

Status exit_execution(List *list, FILE *f){
  if(!list||!f) return ERROR;

  fclose (f);
  list_free(list);

  return OK;
}

int main(int argc, char** argv){
  FILE* f = NULL;
  char line[MAX_LINE];
  int count = 0, n_songs = 0, i;
  Music *mAux;
  List *list;
  
  if(argc != 2) return INVALID_INT;

  if(!(f = fopen(argv[1], "r"))){
    fprintf(stderr, "Error al leer el fichero de texto 1");
    return INVALID_INT;
  }

  if(!(list = list_new())) return INVALID_INT;

  fgets(line, sizeof(line), f);
  n_songs = atoi(line);

  while(count < n_songs){
    fgets(line, sizeof(line), f);
    mAux= music_initFromString(line);
    list_pushBack(list, mAux);
    count++;

    if(count <= n_songs){
      fgets(line, sizeof(line), f);
      mAux= music_initFromString(line);
      list_pushFront(list, mAux);
      count++;
    }
  }

  list_print(stdout, list, music_plain_print);

  fprintf(stdout, "Finished inserting. Now we extrct from the beginning: \n");

  for(i = 0; i<(n_songs/2); i++){
    mAux = (Music*)list_popFront(list);
    music_plain_print(stdout, mAux);
    free(mAux);
  }

  fprintf(stdout, "\nNow we extract from the end: \n");
  
  for(i = 0; i<(n_songs/2); i++){
    mAux = (Music*)list_popBack(list);
    music_plain_print(stdout, mAux);
    free(mAux);
  }

  exit_execution(list, f);

  return EXIT_SUCCESS;
}