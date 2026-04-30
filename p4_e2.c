#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bstree.h"
#include "radio.h"
#include "types.h"
#include "list.h"

int main(int argc, char const *argv[]) {
	FILE *f_in = NULL, *f_out = NULL;
	BSTree *t = NULL;
	Music **songs=NULL, *m;
	const char *mode;
	int n, index=0;
	long	music1_id, music2_id;
	Radio *r = NULL;

	if (argc != 4) {
		printf("Usage: %s music_file music_id_1 music_id_2\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	

  f_in = fopen(argv[1], "r");
  if (!f_in) {
    return (EXIT_FAILURE);
  }
	f_out = stdout;

  r = radio_init();
  if (!r) mainCleanUp (EXIT_FAILURE, r, f_in);
    
  // lee el fichero
  if  (radio_readFromFile(f_in, r) == ERROR) {
    fprintf(stdout, "Not file or File format incorrect\n");
    mainCleanUp (EXIT_FAILURE, r, f_in);
  }
	
	music1_id = atoi(argv[2]);
    music2_id = atoi(argv[3]);
	/* REPLACE BY YOUR OWN IMPLEMENTED FUNCTIONS */
	songs = radio_getMusicList(r);
	n = radio_getNumberOfMusic(r);
	
	index = radio_getPositionFromID(r, music_id);

	m = songs[index];
	if (m == NULL) {
		printf("Error when initialising music with id: %ld\n", music_id);
		mainCleanUp (EXIT_FAILURE, r, f_in);
	}



  
  tree_destroy(t);
  free(songs);
  mainCleanUp (EXIT_SUCCESS, r, f_in);
}