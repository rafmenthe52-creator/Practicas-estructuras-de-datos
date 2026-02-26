#include "p1_e1.h"

int main(void) {
    Music* M1;
    Music* M2;
    Music* M3;
    int comp_Result;
    const char* name_Aux;
    FILE* fp;
    char line[MAX_LINE];


    /* Open radio.txt and check for errors*/
    fp = fopen("radio1.txt", "r");
    if (!fp) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    /* Read number of songs (skip line)*/
    fgets(line, sizeof(line), fp);

    /* Read first song */
    fgets(line, sizeof(line), fp);
    M1 = music_initFromString(line);

    /* Read second song */
    fgets(line, sizeof(line), fp);
    M2 = music_initFromString(line);

    fclose(fp);

    if ((-1 == music_formatted_print(stdout, M1))) {
        fprintf(stdout, "Error while printing song");
        music_free(M1);
        music_free(M2);
        return 0;
    }

    if ((-1 == music_formatted_print(stdout, M2))) {
        fprintf(stdout, "Error while printing song");
        music_free(M1);
        music_free(M2);
        return 0;
    }

    fprintf(stdout, "Equals?");
    comp_Result = music_cmp(M1, M2);
    if (comp_Result == 0) {
        fprintf(stdout, "Yes\n");
    } else {
        fprintf(stdout, "No\n");
    }

    name_Aux = music_getTitle(M2);
    fprintf(stdout, "Music 2 title: %s \n", name_Aux);

    M3 = music_copy(M1);

    fprintf(stdout, "Music 3 id: %ld \n", music_getId(M3));

    if ((-1 == music_formatted_print(stdout, M1))) {
        fprintf(stdout, "Error while printing song");
        music_free(M1);
        music_free(M2);
        music_free(M3);
        return 0;
    }

    if ((-1 == music_formatted_print(stdout, M3))) {
        fprintf(stdout, "Error while printing song");
        music_free(M1);
        music_free(M2);
        music_free(M3);
        return 0;
    }

    fprintf(stdout, "Equals?");
    comp_Result = music_cmp(M1, M3);
    if (comp_Result == 0) {
        fprintf(stdout, "Yes");
    } else {
        fprintf(stdout, "No");
    }

    music_free(M1);
    music_free(M2);
    music_free(M3);

    return 0;
}
