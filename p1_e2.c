#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "music.h"
#include "radio.h"
#include "types.h"

int main(void) {
  Radio* radio;
  long songs_id[MAX_MSC];
  int i;

  radio = radio_init();

  /*Initializing first song*/
  fprintf(stdout, "Inserting Paint It, Black... result...:");
  if ((radio_newMusic(radio, "id:\"111\" title:\"Paint it, Black\" artist:\"The Rolling Stones\" duration:\"202\"")) == OK) {
    fprintf(stdout, "1\n");
  } else {
    fprintf(stdout, "2\n");
    return -1;
  }

  /*Initializing second song*/
  fprintf(stdout, "Inserting Every Breath You Take... result...:");
  if ((radio_newMusic(radio, "id:\"222\" title: \"Every Breath You Take\" artist:\"The Police\" duration:\"253\"")) == OK) {
    fprintf(stdout, "1\n");
  } else {
    fprintf(stdout, "2\n");
    return -1;
  }

  /* get the songs id's */
  for (i = 0; i < radio_getNumberOfMusic(radio); i++) {
    songs_id[i] = radio_getIdFromPosition(radio, i);
  }

  /*Creating relation from 222 to 111*/
  fprintf(stdout, "insering radio recomendation: %ld --> %ld: ", songs_id[1], songs_id[0]);
  if (radio_newRelation(radio, songs_id[1], songs_id[0]) == OK) {
    fprintf(stdout, "1\n");
  } else {
    fprintf(stdout, "0\n");
    return -1;
  }

  /*confirming relation between m1 and m2*/
  fprintf(stdout, "%ld --> %ld?", songs_id[0], songs_id[1]);
  if (TRUE == radio_relationExists(radio, songs_id[0], songs_id[1])) {
    fprintf(stdout, "Yes\n");
  } else {
    fprintf(stdout, "NO\n");
  }

  /*confirming relation between m1 and m2*/
  fprintf(stdout, "%ld --> %ld?: ", songs_id[1], songs_id[0]);
  if (TRUE == radio_relationExists(radio, songs_id[1], songs_id[0])) {
    fprintf(stdout, "Yes\n");
  } else {
    fprintf(stdout, "NO\n");
  }

  /*Getting number of relations from m1*/
  fprintf(stdout, "Number of relations from %ld: %d\n", songs_id[0], radio_getNumberOfRelationsFromId(radio, songs_id[0]));
  /*Getting number of relations from m2*/
  fprintf(stdout, "Number of relations from %ld: %d\n", songs_id[1], radio_getNumberOfRelationsFromId(radio, songs_id[1]));

  radio_print(stdout, radio);

  radio_free(radio);

  return 0;
}
