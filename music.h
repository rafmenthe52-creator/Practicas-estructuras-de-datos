/**
 * @file  music.h
 * @author Profesores EDAT
 * @date February 2026
 * @version 1.0
 * @brief Library to manage TAD Music
 *
 * @details
 *
 * @see
 */

#ifndef MUSIC_H_
#define MUSIC_H_

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define MAX_MSC 4096

 /**
  * @brief State to characterize the Music state (to be used in P2)
  *
  **/
typedef enum {
    NOT_LISTENED, /*!< Music not visited */
    LISTENED,  /*!< Music visited */
    ERROR_MUSIC   /*!< not valid Music */
} State;

/**
 * @brief Data structure to implement the ADT Music. To be defined
 * in Music.c
 *
 **/
 /* START [Music] */
typedef struct _Music Music;
/* END [Music] */


/**
 * @brief Constructor. Initialize a Music.
 *
 * This function allocates memory for a Music and sets its fields to
 * id to 0, title to "", artist to "", duration to 0 and state to NOT_LISTENED.
 *
 * @code
 * // Example of use
 * Music * m;
 * m = Music_init();
 * @endcode
 *
 * @return Return the initialized Music if it was done correctly,
 * otherwise return NULL.
*/
Music* music_init(void);


/**
 * @brief Constructor. Initialize a Music from its description.
 *
 * This function allocates memory for a Music and sets its fields
 * according to the description provided. A description string is
 * a set of key:value pairs separated by any amount of whitespace,
 * where the key can be any of id, tag or state.
 * No space is allowed in the definition of a key:value pair.
 * The key:value pairs can be provided in any order.
 *
 * Examples
 *
 * Music_initFromString("id:1 title:Golden state:LISTENED");
 * Music_initFromString("title:Golden state:LISTENED id:1");
 * Music_initFromString("artist:HUNTR/X state:NOT_LISTENED");
 * Music_initFromString("id:1 state:LISTENED");
 *
 * @param descr String describing the Music.
 *
 * @return Return the initialized Music if it was done correctly,
 * otherwise return NULL.
*/
Music* music_initFromString(char* descr);

/**
 * @brief Destructor. Free the dynamic memory reserved for a Music .
 *
 * @param m Music to free
 */
void music_free(void* m);


/**
 * @brief  Gets the Music id.
 *
 * @param m Music pointer
 *
 * @return  Returns the id of the given Music, or -1 in case of error.
 */
long music_getId(const Music* m);


/**
 * @brief Gets the Music title.
 *
 * @param m Music pointer
 *
 * @return Returns a pointer to the title of the Music, or NULL in
 * case of error.
 */
const char* music_getTitle(const Music* m);


/**
 * @brief Gets the Music artist.
 *
 * @param m Music pointer
 *
 * @return Returns a pointer to the artist of the Music, or NULL in
 * case of error.
 */
const char* music_getArtist(const Music* m);


/**
 * @brief Gets the Music duration.
 *
 * @param m Music pointer
 *
 * @return Returns the duration of the given Music, or -1 in case of error.
 */
unsigned short music_getDuration(const Music* m);


/**
 * @brief Gets the state of a given Music.
 *
 * @param Music pointer
 *
 * @return Returns the state of a given Music, or ERROR_Music in
 * case of error.
 */
State music_getState(const Music* m);

/**
 * @brief Gets the Music index position in the radio.
 *
 * @param m Music pointer
 *
 * @return Returns the index position of the given Music, or -1 in case of error.
 */
int music_getIndex(const Music* m);


/**
 * @brief Modifies the id of a given Music.
 *
 * @param m Music pointer
 * @param id New Music id, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error
 */
Status music_setId(Music* m, const long id);


/**
 * @brief Modifies the title of a given Music
 *
 * @param m Music pointer
 * @param title New Music title, must fit in the Music
 *
 * @return  Returns OK or ERROR in case of error.
 */
Status music_setTitle(Music* m, const char* title);


/**
 * @brief Modifies the artist of a given Music
 *
 * @param m Music pointer
 * @param artist New Music artist, must fit in the Music
 *
 * @return  Returns OK or ERROR in case of error.
 */
Status music_setArtist(Music* m, const char* artist);


/**
 * @brief Modifies the duration of a given Music
 *
 * @param m Music pointer
 * @param duration New Music duration, must fit in the Music
 *
 * @return  Returns OK or ERROR in case of error.
 */
Status music_setDuration(Music* m, const unsigned short duration);


/**
 * @brief Modifies the state of a given Music
 *
 * @param m Music pointer
 * @param state New Music state
 *
 * @return Returns OK or ERROR in case of error.
 */
Status music_setState(Music* m, const State state);

/**
 * @brief Modifies the index position of a given Music
 *
 * @param m Music pointer
 * @param index New Music index position, must fit in the Music
 *
 * @return  Returns OK or ERROR in case of error.
 */
Status music_setIndex(Music* m, const int index);

/**
 * @brief Compares two music.
 *
 * First it compares their ids. If they are equal, then compares
 * their title. If equal, compares artist.
 *
 * @param m1,m2 Music to compare.
 *
 * @return It returns an integer less than or greater than zero if
 * id of m1 is found,  respectively, to be less than or be greater
 * than id of m2. If their are equal, then returns the result of
 * comparing their titles if they are different. If they are equal, then
 * returns the result of comparing their artists
 */
int music_cmp(const void* m1, const void* m2);



/**
 * @brief Compares the duration of two music.
 *
 * @param m1,m2 Music to compare.
 *
 * @return It returns the difference between the duration of both music
 */
int music_duration_cmp(const void* m1, const void* m2);

/**
 * @brief Compares the artists of two music.
 *
 * @param m1,m2 Music to compare.
 *
 * @return It returns the result of comparing the artists
 */
int music_artist_cmp(const void* m1, const void* m2);

/**
 * @brief Reserves memory for a Music where it copies the data from
 * the Music src.
 *
 * @code
 * // Example of use
 * Music *trg, *src;
 * src = music_init();
 * trg = music_copy(src);
 * // .... aditional code ...
 * // free Musics
 * music_free(src);
 * music_free(trg);
 * @endcode
 *
 * @param src Original Music pointer
 *
 * @return Returns the pointer of the copied Music if everything
 * went well, or NULL otherwise.
 */
void* music_copy(const void* src);


/**
 * @brief Prints in pf the data of a Music.
 *
 * Prints the music information without format: [id, title, artist, duration, state], without
 * line break at the end.
 * The type State is an enumeration so it can be printed as an int.
 *
 * @code
 * Music * m;
 * m = music_init();
 * music_plain_print (stdout, v);
 * @endcode
 *
 * @param pf File descriptor
 * @param m Music to be printed
 *
 * @return Returns the number of characters that have been written
 * successfully. If there have been errors returns -1.
 */
int music_plain_print(FILE* pf, const void* m);


/**
 * @brief Prints in pf the formatted data of a Music.
 *
 *  ɴᴏᴡ ᴘʟᴀʏɪɴɢ: [title]
 *   • Artist [artist] •
 * ────────⚪────────
 *      ◄◄⠀▐▐ ⠀►►
 *  0:00 / [duration format XX:XX] ───○ 🔊⠀
 *
 * @code
 * Music * m;
 * m = music_init();
 * music_formatted_print (stdout, v);
 * @endcode
 *
 * @param pf File descriptor
 * @param m Music to be printed
 *
 * @return Returns the number of characters that have been written
 * successfully. If there have been errors returns -1.
 */
int music_formatted_print(FILE* pf, const void* m);


#endif /* Music_H_ */
