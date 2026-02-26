#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "music.h"
#include "radio.h"
#include "types.h"

int main(int argc, char* argv[]) {
  FILE* f;
  Radio* r;

  if (argc != 2) {
    return -1;
  }

  f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Error al leer el fichero de texto");
    return -1;
  }

  r = radio_init();

  if (radio_readFromFile(f, r) == ERROR) {
    return -1;
  }

  fprintf(stdout, "Radio recomendations:\n");

  radio_print(stdout, r);

  fclose(f);
  radio_free(r);

  return 0;
}
