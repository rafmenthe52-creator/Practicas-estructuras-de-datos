#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bstree.h"
#include "radio.h"
#include "types.h"
#include "list.h"


int mainCleanUp(int ret_value, Radio* r, FILE* pf) {
	radio_free(r);
	fclose(pf);
	exit(ret_value);
}

int main(int argc, char const* argv[]) {
	FILE* f_in = NULL, * f_out = NULL;
	BSTree* t = NULL;
	List* list = NULL;
	Music** songs = NULL, * m1, * m2;
	int n, i;
	long	music1_id, music2_id;
	Radio* r = NULL;

	if (argc != 4) {
		printf("Usage: %s music_file music_id_1 music_id_2\n", argv[0]);
		exit(EXIT_FAILURE);
	}



	f_in = fopen(argv[1], "r");
	if (!f_in) {
		fprintf(stdout, "ERROR");
		return (EXIT_FAILURE);
	}
	f_out = stdout;

	r = radio_init();
	if (!r) mainCleanUp(EXIT_FAILURE, r, f_in);

	// lee el fichero
	if (radio_readFromFile(f_in, r) == ERROR) {
		fprintf(f_out, "Not file or File format incorrect\n");
		mainCleanUp(EXIT_FAILURE, r, f_in);
	}

	music1_id = atoi(argv[2]);
	music2_id = atoi(argv[3]);
	/* REPLACE BY YOUR OWN IMPLEMENTED FUNCTIONS */
	songs = radio_getMusicList(r);
	n = radio_getNumberOfMusic(r);

	m1 = songs[radio_getPositionFromID(r, music1_id)];
	m2 = songs[radio_getPositionFromID(r, music2_id)];

	if (m1 == NULL) {
		printf("Error when initialising music with id: %ld\n", music1_id);
		mainCleanUp(EXIT_FAILURE, r, f_in);
	}
	if (m2 == NULL) {
		printf("Error when initialising music with id: %ld\n", music2_id);
		mainCleanUp(EXIT_FAILURE, r, f_in);
	}

	t = tree_init(music_plain_print, music_cmp);

	for (i = 0; i < n; i++) {
		if (tree_insert(t, songs[i]) == ERROR) {
			fprintf(f_out, "Music ");
			music_plain_print(f_out, songs[i]);
			fprintf(f_out, " not inserted!\n");
		}
	}

	if ((list = tree_rangeSearch(t, m1, m2)) == NULL) {
		fprintf(f_out, "ERROR while searching in the tree");
	}

	if (list_print(f_out, list, music_plain_print) == INVALID_INT) {
		fprintf(f_out, "ERROR printing the list");
	}


	tree_destroy(t);
	list_free(list);
	free(songs);
	mainCleanUp(EXIT_SUCCESS, r, f_in);
}

/**
 * Respuesta a la pregunta:
 *
 * Se observa que la lista esta ordenada de menor a mayor según su id. Esto se debe al diseño y a la forma de recorrer el árbol.
 * En este caso hemos utilizado un recorrido "in order", por lo que los elementos se van insertando en la lista por orden de menor a mayor
 */