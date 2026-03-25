#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "music.h"
#include "radio.h"
#include "queue.h"
#include "file_utils.h"
#include "types.h"

int now_playing_menu(Queue* history) {
	int option;
	Music* m = NULL;

	/* Obtenemos canción actual del top de la pila */
	m = (Music*)queue_getFront(history);
	if (m != NULL) {
		music_formatted_print(stdout, m);
	} else {
		printf("\nNo song currently playing.\n");
	}

	/* Imprimimos historial (pila) */
	printf("\nUpcoming:\n");
	queue_print(stdout, history, music_plain_print);

	/* Mostramos menu y esperamos selección */
	printf("\n1. Next song\n");
	printf("2. Exit\n");
	printf("Choose an option: ");

	scanf("%d", &option);

	return option;
}

void exit_execution(Radio* radio, Music** list, Queue* q, FILE* f) {
	free(list);
	radio_free(radio);
	queue_free(q);
	fclose(f);

	return;
}

int main(int argc, char** argv) {
	FILE* f;
	Radio* r;
	Queue* q;
	Music** list;
	int i, mReturn;

	if (argc != 2) {
		return -1;
	}

	f = fopen(argv[1], "r");
	if (f == NULL) {
		fprintf(stderr, "Error al leer el fichero de texto 1");
		return -1;
	}

	r = radio_init();

	if (radio_readFromFile(f, r) == ERROR) {
		return -1;
	}

	q = queue_new();

	list = radio_getMusicList(r);

	for (i = 0; i < radio_getNumberOfMusic(r); i++) {
		queue_push(q, list[i]);
	}

	while ((mReturn = now_playing_menu(q)) != 2) {
		if (mReturn == 1) {
			queue_pop(q);
		}
	}

	exit_execution(r, list, q, f);

	return 0;
}