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
	Music** songs = NULL;
	int n, i, count = 0, duration = 0;
	Radio* r = NULL;

	if (argc != 3) {
		printf("Usage: %s music_file min_duration\n", argv[0]);
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

	duration = atoi(argv[2]);
	/* REPLACE BY YOUR OWN IMPLEMENTED FUNCTIONS */
	songs = radio_getMusicList(r);
	n = radio_getNumberOfMusic(r);

	if (duration <= 0) {
		printf("Error when reading min duration (it has to be greater than 0)");
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

	if ((count = tree_countLongSongs(t, duration)) < 0) {
		fprintf(f_out, "ERROR while searching in the tree");
	}

	fprintf(f_out, "Número de canciones con duración mayor a %d: %d\n", duration, count);


	tree_destroy(t);
	free(songs);
	mainCleanUp(EXIT_SUCCESS, r, f_in);
}