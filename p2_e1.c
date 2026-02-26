#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "types.h"
#include "music.h"
#include "radio.h"
#include "stack.h"

int show_player_menu(Stack* history);
int show_player_menu(Stack* history) {
	int option;
	Music* m = NULL;

	/* Obtenemos canción actual del top de la pila */
	m = (Music*)stack_top(history);
	if (m != NULL) {
		music_formatted_print(stdout, m);
	} else {
		printf("\nNo song currently playing.\n");
	}

	/* Imprimimos historial (pila) */
	printf("\nRecently Played:\n");
	stack_print(stdout, history, music_plain_print);

	/* Mostramos menu y esperamos selección */
	printf("\n1. Back to previous song\n");
	printf("2. Exit\n");
	printf("Choose an option: ");

	scanf("%d", &option);z

	return option;
}

void exit_execution(Radio* radio, Music** list, Stack* s, FILE *f) {
  free(list);
  radio_free(radio);
  stack_free(s);
  fclose(f);

  return;
}

/* TODO MAIN FUNCTION */
int main(int argc, char** argv) {
	FILE* f;
	Radio* r;
	Stack* s;
	Music** list;
	int i, mReturn;

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

	s = stack_init();

	list = radio_getMusicList(r);

	for (i = 0; i < radio_getNumberOfMusic(r); i++) {
		stack_push(s, list[i]);
	}

	while ((mReturn=show_player_menu(s)) != 2) {
    if(mReturn==1){
      stack_pop(s);
    }
	}

  exit_execution(r, list, s, f);

	return 0;
}


