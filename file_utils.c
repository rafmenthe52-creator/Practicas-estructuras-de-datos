#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"

#define BUFFER_SIZE 512

//---------------------------------------------------------
// functions to manage pointer types
//---------------------------------------------------------

// INT
int *int_init(int a) {
  int *r = NULL;

  r = (int *)malloc(sizeof(int));
  if (!r) {
    fprintf(stderr, "%s", strerror(errno));
    return NULL;
  }
  *r = a;
  return r;
}

int int_cmp(const void *c1, const void *c2) {
  if (!c1 || !c2)
    return 0;

  return (*(int *)c1 - *(int *)c2);
}

void *int_copy(const void *a) {
  int *c = NULL;

  if (!a)
    return NULL;

  c = int_init(*(int *)a);
  return (void *)c;
}

void int_free(void *a) { free((int *)a); }

int int_print(FILE *pf, const void *a) { return fprintf(pf, "%d", *(int *)a); }

// CHAR
char *char_init(char a) {
  char *r = NULL;

  r = (char *)malloc(sizeof(char));
  if (!r) {
    fprintf(stderr, "%s", strerror(errno));
    return NULL;
  }
  *r = a;
  return r;
}

void *char_copy(const void *a) {
  char *c = NULL;

  if (!a)
    return NULL;

  c = char_init(*(char *)a);
  return (void *)c;
}

int char_cmp(const void *c1, const void *c2) {
  if (!c1 || !c2)
    return 0;

  return (*(char *)c1 - *(char *)c2);
}

void char_free(void *a) { free((char *)a); }

int char_print(FILE *pf, const void *a) {
  if (!pf || !a)
    return -1;

  return fprintf(pf, "%c", *(char *)a);
}

// FLOAT
float *float_init(float a) {
  float *r = NULL;

  r = (float *)malloc(sizeof(float));
  if (!r) {
    fprintf(stderr, "%s", strerror(errno));
    return NULL;
  }
  *r = a;
  return r;
}

void *float_copy(const void *a) {
  float *c = NULL;

  if (!a)
    return NULL;

  c = float_init(*(float *)a);
  return (void *)c;
}

int float_cmp(const void *c1, const void *c2) {
  if (!c1 || !c2)
    return 0;
  if (*(float *)c1 > *(float *)c2)
    return 1;
  else if (*(float *)c2 > *(float *)c1)
    return -1;
  else
    return 0;
}

void float_free(void *a) { free((float *)a); }

int float_print(FILE *pf, const void *a) {
  if (!pf || !a)
    return -1;
  return fprintf(pf, "%f", *(float *)a);
}

//  String
void *string_copy(const void *src) { return strdup(src); }

int string_cmp(const void *c1, const void *c2) {
  if (!c1 || !c2)
    return 0;

  return (strcmp(*(char **)c1, *(char **)c2));
}

void string_free(void *src) { free((char *)src); }

int string_print(FILE *pf, const void *src) {
  if (!pf || !src)
    return -1;
  return fprintf(pf, "%s", (char *)src);
}

