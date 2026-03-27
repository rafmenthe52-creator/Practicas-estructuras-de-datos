#include <stdio.h>
#include "list.h"
#include "radio.h"

int main(int argc, char** argv){
  FILE* f;
  Radio* r1;
  char* line;
  
  if(argc != 2) return INVALID_INT;

  if(!(f = fopen(argv[1], "r"))){
    fprintf(stderr, "Error al leer el fichero de texto 1");
    return INVALID_INT;
  }

}