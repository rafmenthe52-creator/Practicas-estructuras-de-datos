#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "radio.h"
#include "music.h"
#include "stack.h"

int main(int argc, char** argv) {
  FILE* f1;
  Radio* r1;
  long id_from, id_to;

  if (argc != 4) {
    return -1;
  }

  f1 = fopen(argv[1], "r");
  if (f1 == NULL) {
    fprintf(stderr, "Error al leer el fichero de texto 1");
    return -1;
  }

  id_from = atol(argv[2]);
  id_to = atol(argv[3]);

  r1 = radio_init();

  if (radio_readFromFile(f1, r1) == ERROR) {
    return -1;
  }

  fprintf(stdout, "Radio:\n");
  radio_print(stdout, r1);

  if (ERROR == radio_depthSearch(r1, id_from, id_to)) {
    return -1;
  }

  return 0;
}