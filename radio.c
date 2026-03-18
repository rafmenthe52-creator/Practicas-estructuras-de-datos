#include "radio.h"


struct _Radio {
  Music* songs[MAX_MSC];
  Bool relations[MAX_MSC][MAX_MSC];
  int num_music;
  int nume_relations;
};
/*
Private functions
*/

int radio_getPositionFromID(const Radio* r, long id) {
  int i;

  if (!r || id < 0) {
    return POSITION_NOT_FOUND;
  }

  for (i = 0; i < r->num_music; i++) {
    if (music_getId(r->songs[i]) == id) {
      return i;
    }
  }

  return POSITION_NOT_FOUND;
}

Music* radio_getMusicFromId(Radio* r, long id) {
  int i;

  if (id < 0) {
    return NULL;
  }

  for (i = 0; i < r->num_music; i++) {
    if (music_getId(r->songs[i]) == id) {
      return r->songs[i];
    }
  }
}

/*
Public functions
*/

long radio_getIdFromPosition(const Radio* r, int pos) {
  if (!r || pos > r->num_music) {
    return ERROR;
  }

  return music_getId(r->songs[pos]);
}

Radio* radio_init(void) {
  Radio* radio;
  int i = INIT_VALUE, j = INIT_VALUE;

  /*Allocate dynamic memory*/
  radio = (Radio*)malloc(1 * sizeof(Radio));

  /*Initialize non-array vatiables*/
  radio->num_music = INIT_VALUE;
  radio->nume_relations = INIT_VALUE;

  /*Initialize array variables to NULL*/
  for (i = 0; i < MAX_MSC; i++) {
    radio->songs[i] = NULL;
  }

  for (i = 0; i < MAX_MSC; i++) {
    for (j = 0; j < MAX_MSC; j++) {
      radio->relations[i][j] = INIT_VALUE;
    }

  }

  return radio;
}


void radio_free(Radio* r) {
  int i;

  for (i = 0;i < r->num_music;i++) {
    music_free(r->songs[i]);
  }

  free(r);
}

Status radio_newMusic(Radio* r, char* desc) {
  Music* songaux;
  long int idaux;

  if (!r || !desc) {
    return ERROR;
  }



  if (r->num_music >= MAX_MSC) {
    return ERROR;
  }

  songaux = music_initFromString(desc);
  idaux = music_getId(songaux);

  if (radio_contains(r, idaux)) {
    return OK;
  }else{
    r->songs[r->num_music] = songaux;
    music_setIndex(songaux, r->num_music);
  }

  r->num_music++;

  return OK;
}

Status radio_newRelation(Radio* r, long orig, long dest) {
  if (!r || !orig || !dest) {
    return ERROR;
  }

  /*Check if one of the ids isn't in the struct*/
  if (radio_contains(r, orig) == FALSE || radio_contains(r, dest) == FALSE) {
    return ERROR;
  }

  if (radio_relationExists(r, orig, dest)) {
    return ERROR;
  }

  /*No need to check if the id that is input into getPositionFromID, since we know that the song with that id is inside the struct*/
  r->relations[radio_getPositionFromID(r, orig)][radio_getPositionFromID(r, dest)] = TRUE;

  return OK;
}

Bool radio_contains(const Radio* r, long id) {
  if (!r || id < 0) {
    return FALSE;
  }

  return (radio_getPositionFromID(r, id) != POSITION_NOT_FOUND) ? TRUE : FALSE;
}

int radio_getNumberOfMusic(const Radio* r) {
  if (!r) {
    return -1;
  }

  return r->num_music;
}

int radio_getNumberOfRelations(const Radio* r) {
  if (!r) {
    return -1;
  }

  return r->nume_relations;
}

Bool radio_relationExists(const Radio* r, long orig, long dest) {
  if (!r || !orig || !dest) {
    return FALSE;
  }

  /*Check if one of the ids isn't in the struct*/
  if (radio_contains(r, orig) == FALSE || radio_contains(r, dest) == FALSE) {
    return FALSE;
  }

  /* Relations will be TRUE (1) if the relation exist, therefore it will return TRUE */
  if (r->relations[radio_getPositionFromID(r, orig)][radio_getPositionFromID(r, dest)]) {
    return TRUE;
  }

  return FALSE;
}

int radio_getNumberOfRelationsFromId(const Radio* r, long id) {
  int i = 0, count = 0;

  if (!r || !id) {
    return ERROR;
  }

  for (i = 0; i < radio_getNumberOfMusic(r); i++) {
    if (r->relations[radio_getPositionFromID(r, id)][i]) {
      count++;
    }
  }

  return count;
}

long* radio_getRelationsFromId(const Radio* r, long id) {
  int n_relations, i = 0, j = 0;
  long* list;

  if (!r || !id) {
    return NULL;
  }

  n_relations = radio_getNumberOfRelationsFromId(r, id);

  list = (long*)malloc(n_relations * sizeof(long));

  for (i = 0; i < radio_getNumberOfMusic(r); i++) {
    if (r->relations[radio_getPositionFromID(r, id)][i]) {
      list[j] = radio_getIdFromPosition(r, i);
      j++;
    }
  }

  return list;
}

int radio_print(FILE* pf, const Radio* r) {
  int counter = 0, i, j, num_relations;
  long* relations;
  long music_id;

  if (!pf || !r) {
    return -1;
  }

  for (i = 0; i < r->num_music; i++) {
    music_id = music_getId(r->songs[i]);
    counter = music_plain_print(pf, r->songs[i]);
    counter += fprintf(pf, ": ");
    
    num_relations = radio_getNumberOfRelationsFromId(r, music_id);
    if (num_relations > 0) {
      relations = radio_getRelationsFromId(r, music_id);
      for (j = 0; j < num_relations; j++) {
        counter += music_plain_print(pf, radio_getMusicFromId(r, relations[j]));
      }
      free(relations);
    }
    
    fprintf(pf, "\n");
  }

  return counter;
}

Status radio_readFromFile(FILE* fin, Radio* r) {
  int i, j, auxnum_music;
  char line[MAX_LINE];
  char* tok;
  long music_id;
  long music_relations_id[MAX_MSC];

  if (!fin || !r) {
    return ERROR;
  }

  if (!fgets(line, sizeof(line), fin)) {
    return ERROR;
  }

  auxnum_music = atoi(line);

  for (i = 0; i < auxnum_music; i++) {
    fgets(line, sizeof(line), fin);
    radio_newMusic(r, line);
  }

  j = 0;
  while (fgets(line, sizeof(line), fin)) {

    tok = strtok(line, " ");
    music_id = atoi(tok);

    tok = strtok(NULL, " ");

    while (tok != NULL) {

      music_relations_id[j] = atoi(tok);

      radio_newRelation(r, music_id, music_relations_id[j]);

      j++;

      tok = strtok(NULL, " ");
    }
  }

  return OK;
}

Music** radio_getMusicList(Radio* radio) {
  Music** musicList;
  int i;

  if (!radio) {
    return NULL;
  }
  musicList = (Music**)malloc(radio->num_music * sizeof(Music*));

  for (i = 0; i < radio->num_music; i++) {
    musicList[i] = radio->songs[i];
  }

  return musicList;
}

Status radio_depthSearch(Radio* r, long from_id, long to_id) {
  Status status = OK;
  Stack* stack;
  long* relations;
  Music* musicCurrent;
  int i;

  if (!r || from_id < 0 || to_id < 0) {
    return ERROR;
  }

  stack = stack_init();

  music_setState(radio_getMusicFromId(r, from_id), LISTENED);

  stack_push(stack, radio_getMusicFromId(r, from_id));

  while (stack_isEmpty(stack) == FALSE || status == OK) {
    musicCurrent = stack_pop(stack);
    music_plain_print(stdout, musicCurrent);

    if (music_getId(musicCurrent) == to_id) {
      status = FINISHED;
    } else {
      relations = radio_getRelationsFromId(r, musicCurrent);
      for (i = 0; i < radio_getNumberOfRelationsFromId(r, music_getId(musicCurrent)); i++) {
        if (music_getState(radio_getMusicFromId(r, relations[i])) == NOT_LISTENED) {
          /*Change state to listened*/
          music_setState(radio_getMusicFromId(r, relations[i]), LISTENED);
          /*Push the related music to the stack*/
          stack_push(stack, radio_getMusicFromId(r, relations[i]));
        }
      }
      free(relations);
    }
  }
  stack_free(stack);

  return status;
}