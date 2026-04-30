#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "radio.h"
#include "types.h"

/* START Private methods */
int mainCleanUp (int ret_value, Radio *r, FILE *pf) {
  radio_free(r);   
  fclose(pf);
  exit(ret_value);
}

void loadBalancedTree_rec(Music **sorted_data, BSTree *t, int first, int last) {
  int middle = (first + last) / 2;
  Music *m;

  if (first <= last) {
    m = *(&(sorted_data[0]) + middle);
    if (tree_insert(t, m) == ERROR) {
      fprintf(stdout, "Music ");
      music_plain_print(stdout, m);
      fprintf(stdout, " not inserted!\n");
    }

    loadBalancedTree_rec(sorted_data, t, first, middle - 1);
    loadBalancedTree_rec(sorted_data, t, middle + 1, last);
  }
}

BSTree *loadBalancedTree(Music **data, int n) {
  BSTree *t;

  if (!data || (n <= 0)) {
    return NULL;
  }

  if (!(t = tree_init(music_plain_print, music_cmp))) { 
    return NULL;
  }

  loadBalancedTree_rec(data, t, 0, n - 1);

  return t;
}

BSTree *loadUnbalancedTree(Music **data, int n) {
  BSTree *t;
  Music *m;
  int i;

  if (!data || (n <= 0)) {
    return NULL;
  }

  if (!(t = tree_init(music_plain_print, music_cmp))) {
    return NULL;
  }

  for (i = 0; i < n; i++) {
    m = data[i];
    if (tree_insert(t, m) == ERROR) {
      fprintf(stdout, "Music ");
      music_plain_print(stdout, m);
      fprintf(stdout, " not inserted!\n");
    }
  }

  return t;
}

int qsort_fun(const void *e1, const void *e2){
  Music **pm1, **pm2;

  pm1 = (Music **) e1;
  pm2 = (Music **) e2;

  return music_cmp(*pm1, *pm2);
}
/* END Private methods */


int main(int argc, char const *argv[]) {
	FILE *f_in = NULL, *f_out = NULL;
	BSTree *t = NULL;
	Music **songs=NULL, *m;
	const char *mode;
	int n, index=0;
	long	music_id;
	time_t time;
	Radio *r = NULL;

	if (argc != 4) {
		printf("Usage: %s music_file music_id mode[normal|sorted]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	mode = argv[3];
	if (strcmp(mode, "normal") && strcmp(mode, "sorted")) {
		printf("Incorrect mode: %s\n", mode);
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
	
	music_id = atoi(argv[2]);
	/* REPLACE BY YOUR OWN IMPLEMENTED FUNCTIONS */
	songs = radio_getMusicList(r);
	n = radio_getNumberOfMusic(r);
	
	index = radio_getPositionFromID(r, music_id);

	m = songs[index];
	if (m == NULL) {
		printf("Error when initialising music with id: %ld\n", music_id);
		mainCleanUp (EXIT_FAILURE, r, f_in);
	}
	/* END REPLACE */

	if (!strcmp(mode, "normal")) {
		fprintf(f_out, "Mode: normal\n");
		time = clock();
		t = loadUnbalancedTree(songs, n);
		time = clock() - time;
	}
	else {
		qsort(songs, n, sizeof(Music *), qsort_fun);
		fprintf(f_out, "Mode: sorted\n");
		time = clock();
		t = loadBalancedTree(songs, n);
		time = clock() - time;
	}

  if (!t) {
    mainCleanUp (EXIT_FAILURE, r, f_in);
  }

  fprintf(f_out, "Tree building time: %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);
  fprintf(f_out, "Tree size: %ld\nTree depth: %d\n", tree_size(t), tree_depth(t));

  fprintf(f_out, "Min element in tree: ");
  time = clock();
  music_plain_print(f_out, tree_find_min(t));
  time = clock() - time;
  fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);

  fprintf(f_out, "Max element in tree: ");
  time = clock();
  music_plain_print(f_out, tree_find_max(t));
  time = clock() - time;
  fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);

  time = clock();
  if (tree_contains(t, m) == TRUE) {
    fprintf(f_out, "Element found");
    time = clock() - time;
    fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);


    fprintf(f_out, "Removing element in tree: ");
    time = clock();
    fprintf(f_out, "%s", tree_remove(t, m) == OK ? "OK" : "ERR");
    time = clock() - time;
    fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);
    fprintf(f_out, "Tree size: %ld\nTree depth: %d\n", tree_size(t), tree_depth(t));

  } else {
    fprintf(f_out, "Element NOT found");
    time = clock() - time;
    fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);
  }
  
  tree_destroy(t);
  free(songs);
  mainCleanUp (EXIT_SUCCESS, r, f_in);
}