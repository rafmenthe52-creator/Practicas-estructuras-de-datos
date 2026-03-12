/**
 * @file  music.c
 * @author Profesores EDAT
 * @date February 2026
 * @mersion 1.0
 * @brief Library to manage ADT Music
 *
 * @details
 *
 * @see
 */

#include <string.h>
#include "music.h"


 /* START [STR_LENGTH] */
#define STR_LENGTH 64
/* END [STR_LENGTH] */

/* Music declaration goes here */
/**
 * @brief Data structure to implement the ADT Music. To be defined
 * in Music.c
 *
 **/
struct _Music {
  long int id;
  char title[STR_LENGTH];
  char artist[STR_LENGTH];
  unsigned short duration;
  State state;
};
/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status music_setField(Music* m, char* key, char* value);

Status music_setField(Music* m, char* key, char* value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return music_setId(m, atol(value));
  } else if (strcmp(key, "title") == 0) {
    return music_setTitle(m, value);
  } else if (strcmp(key, "artist") == 0) {
    return music_setArtist(m, value);
  } else if (strcmp(key, "duration") == 0) {
    return music_setDuration(m, atol(value));
  } else if (strcmp(key, "state") == 0) {
    return music_setState(m, (State)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Music* music_initFromString(char* descr) {
  Music* m;
  char* p;
  char* key_start;
  char* value_start;
  char* buffer;

  if (!descr) return NULL;

  buffer = strdup(descr);          /* copiar entrada */
  if (!buffer) return NULL;

  m = music_init();
  if (!m) {
    free(buffer);
    return NULL;
  }

  p = buffer;

  while (*p) {
    /* Skip whitespace */
    while (*p == ' ' || *p == '\t' || *p == '\n')
      p++;

    if (!*p) break;

    /* Parse key */
    key_start = p;
    while (*p && *p != ':')
      p++;

    if (!*p) break;
    *p++ = '\0';   /* terminate key */

    /* Skip whitespace after colon */
    while (*p == ' ' || *p == '\t' || *p == '\n')
      p++;

    /* Expect opening quote */
    if (*p != '"') break;
    p++;

    /* Parse value */
    value_start = p;
    while (*p && *p != '"')
      p++;

    if (!*p) break;
    *p++ = '\0';   /* terminate value */

    music_setField(m, key_start, value_start);
  }

  free(buffer);
  return m;
}


/**  Remaining functions of music.h to be implemented here **/

Music* music_init(void) {
  Music* music = NULL;

  if (!(music = (Music*)malloc(1 * sizeof(Music)))) {
    return NULL;
  }

  music_setId(music, 0);
  music_setTitle(music, "");
  music_setArtist(music, "");
  music_setDuration(music, 0);
  music_setState(music, NOT_LISTENED);

  return music;
}

void music_free(void* m) {
  free(m);
}

long music_getId(const Music* m) {
  if(!m){
    return NULL;
  }

  return m->id;
}

const char* music_getTitle(const Music* m) {
  if(!m){
    return NULL;
  }

  return m->title;
}

const char* music_getArtist(const Music* m) {
  if(!m){
    return NULL;
  }

  return m->artist;
}

unsigned short music_getDuration(const Music* m) {
  if(!m){
    return NULL;
  }
 
  return m->duration;
}

State music_getState(const Music* m) {
  if(!m){
    return NULL;
  }
  
  return m->state;
}

Status music_setId(Music* m, const long id) {
  if (!m || !id) {
    return ERROR;
  }

  if (id < 0) {
    return ERROR;
  }
  m->id = id;

  return OK;
}

Status music_setTitle(Music* m, const char* title) {
  if (!m || !title) {
    return ERROR;
  }

  if (strlen(title) > STR_LENGTH-1) {
    return ERROR;
  }

  strcpy(m->title, title);

  return OK;
}

Status music_setArtist(Music* m, const char* artist) {
  if (!m || !artist) {
    return ERROR;
  }

  if (strlen(artist) > STR_LENGTH-1) {
    return ERROR;
  }

  strcpy(m->artist, artist);
  return OK;
}

Status music_setDuration(Music* m, const unsigned short duration) {
  if (!m || !duration) {
    return ERROR;
  }

  m->duration = duration;

  return OK;
}

Status music_setState(Music* m, const State state) {
  if (!m || !state) {
    return ERROR;
  }

  if ((state != NOT_LISTENED) && (state != LISTENED) && (state != ERROR_MUSIC)) {
    return ERROR;
  }

  m->state = state;
  return OK;
}

int music_cmp(const void* m1, const void* m2) {
  Music* music1;
  Music* music2;
  music1 = (Music*)(m1);
  music2 = (Music*)(m2);

  if (music1->id == music2->id) {
    if (0 == strcmp(music1->title, music2->title)) {
      return (strcmp(music1->artist, music2->artist));
    } else {
      return strcmp(music1->title, music2->title);
    }
  } else if (music1->id > music2->id) {
    return 1;
  } else {
    return -1;
  }
}

int music_duration_cmp(const void* m1, const void* m2){
  Music *music1, *music2;
  
  music1=(Music*)(m1);
  music2=(Music*)(m2);

  return music1->duration-music2->duration;
}

int music_artist_cmp(const void* m1, const void* m2){
  Music *music1, *music2;

  music1=(Music*)(m1);
  music2=(Music*)(m2);

  return strcmp(music1->artist, music2->artist);
}

void* music_copy(const void* src) {
  Music* music_in;
  Music* music_out;

  music_in = (Music*)(src);

  music_out = music_init();

  music_out->id = music_in->id;
  strcpy(music_out->artist, music_in->artist);
  strcpy(music_out->title, music_in->title);
  music_out->duration = music_in->duration;
  music_out->state = music_in->state;

  return music_out;
}

int music_plain_print(FILE* pf, const void* m) {
  Music* music;
  int count;

  if (!pf || !m) {
    return -1;
  }

  music = (Music*)(m);

  count = fprintf(pf, "[%ld, %s, %s, %hu, %d]", music->id, music->title, music->artist, music->duration, music->state);

  return count;
}

int music_formatted_print(FILE* pf, const void* m) {
  Music* aux;
  int counter = 0, minutes, sec;
  if (!pf || !m) return -1;

  aux = (Music*)m;

  if (!aux->duration || aux->duration <= 0) return -1;
  minutes = aux->duration / 60;
  sec = aux->duration % 60;

  counter = fprintf(pf, "\t ɴᴏᴡ ᴘʟᴀʏɪɴɢ: %s\n", aux->title);
  counter += fprintf(pf, "\t • Artist %s •\n", aux->artist);
  counter += fprintf(pf, "\t──────────⚪──────────\n");
  counter += fprintf(pf, "\t\t◄◄⠀▐▐ ⠀►►\n");
  counter += fprintf(pf, "\t 0:00 / %02d:%02d ───○ 🔊⠀\n\n", minutes, sec);

  return counter;
}
