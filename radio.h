/**
 * @file radio.h
 * @author Profesores EDAT
 * @date February 2026
 * @version 1.0
 * @brief Library to manage the radio TAD
 *
 * @see
 */

#ifndef RADIO_H
#define RADIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "music.h"

#define MAX_MSC 4096
#define MAX_LINE 256

typedef struct _Radio Radio;

/**
 * @brief Creates a new empty radio.
 *
 * Allocates memory for a new radio and initializes it to be empty
 * (no music and no relations).
 *
 * @return A pointer to the radio if it was correctly allocated,
 * NULL otherwise.
 **/
Radio* radio_init(void);

/**
 * @brief Frees a radio.
 *
 * Frees all the memory allocated for the radio.
 *
 * @param r Pointer to radio to be free.
 **/
void radio_free(Radio* r);

/**
 * @brief Inserts a new music in a radio.
 *
 * Creates a music by calling music_initFromString and adds it to
 * a radio. If a music with the same id already exists in the radio,
 * it is not added.
 *
 * @param r Pointer to the radio.
 * @param desc Description of the music.
 *
 * @return Returns OK if the music could be created (or if it exists
 * already), ERROR otherwise.
 **/
Status radio_newMusic(Radio* r, char* desc);

/**
 * @brief Creates a relation between two music of a radio.
 *
 * If any of the two music does not exist in the radio the relation is
 * not created.
 *
 * @param r Pointer to the radio.
 * @param orig ID of the origin music.
 * @param dest ID of the destination music.
 *
 * @return OK if the relation could be added to the radio, ERROR otherwise.
 **/
Status radio_newRelation(Radio* r, long orig, long dest);

/**
 * @brief Checks if a radio contains a music.
 *
 * @param r Pointer to the radio.
 * @param id ID of the music.
 *
 * @return Returns TRUE if there is a music in the radio g with the
 * ID id, FALSE otherwise.
 **/
Bool radio_contains(const Radio* r, long id);

/**
 * @brief Returns the total number of music in a radio.
 *
 * @param r Pointer to the radio.
 *
 * @return Returns The number of music in the radio, or -1 if
 * there is any error.
 **/
int radio_getNumberOfMusic(const Radio* r);

/**
 * @brief Returns the total number of relations in the radio.
 *
 * @param r Pointer to the radio.
 *
 * @return Returns The number of relations in the radio, or -1 if
 * there is any error.
 **/
int radio_getNumberOfRelations(const Radio* r);

/**
 * @brief Determines if there is a relation between a pair of music.
 *
 * @param r Pointer to the radio.
 * @param orig ID of the origin music.
 * @param dest ID of the destination music.
 *
 * @return Returns TRUE if there is a relation in r from orig
 *  to dest, FALSE otherwise.
 **/
Bool radio_relationExists(const Radio* r, long orig, long dest);

/**
 * @brief Gets the number of relations starting at a given music.
 *
 * @param r Pointer to the radio.
 * @param id ID of the origin music.
 *
 * @return Returns the total number of relation starting at
 * music with ID id, or -1 if there is any error.
 **/
int radio_getNumberOfRelationsFromId(const Radio* r, long id);

/**
 * @brief Returns an array with the ids of all the music which a
 * given music connects to.
 *
 * This function allocates memory for the array.
 *
 * @param r Pointer to the radio.
 * @param id ID of the origin music.
 *
 * @return Returns an array with the ids of all the music to which
 * the music with ID id is connected, or NULL if there is any error.
 */
long* radio_getRelationsFromId(const Radio* r, long id);

/**
 * @brief gets the id of a song from his position
 *
 * @param r Pointer to the radio.
 * @param pos the position of the song in the radio.
 *
 * @return returns the song's id
 */
long radio_getIdFromPosition(const Radio* r, int pos);


/**
 * @brief Prints a radio.
 *
 * Prints the radio g to the file pf.
 * The format to be followed is: print a line by music with the
 * information associated with the music and then their connections
 *
 * For example:
 * [317, Golden, Huntrix, 194, 0]:
 * [482, Watermelon Sugar, Harry Styles, 174, 0]: [317, Golden, Huntrix, 194, 0]
 * [105, Don't Stop Believin, Journey, 251, 0]: [231, Livin' on a Prayer, Bon Jovi, 249, 0]
 * [231, Livin' on a Prayer, Bon Jovi, 249, 0]: [105, Don't Stop Believin, Journey, 251, 0] [764, Sweet Child O' Mine, Guns N' Roses, 356, 0]
 * [764, Sweet Child O' Mine, Guns N' Roses, 356, 0]: [231, Livin' on a Prayer, Bon Jovi, 249, 0]
 *
 * @param pf File descriptor.
 * @param r Pointer to the radio.
 *
 * @return The number of characters printed, or -1 if there is any error.
 */
int radio_print(FILE* pf, const Radio* r);


/**
 * @brief Reads a radio definition from a text file.
 *
 * Reads a radio description from the text file pointed to by fin,
 * and fills the radio r.
 *
 * The first line in the file contains the number of music.
 * Then one line per music with the music description.
 * Finally one line per relation, with the ids of the origin and
 * the destination (this is one way only)
 *
 * For example:
 *
 * 5
 * id:"317" title:"Golden" artist:"Huntrix" duration:"194"
 * id:"482" title:"Watermelon Sugar" artist:"Harry Styles" duration: "174"
 * id:"105" title:"Don't Stop Believin" artist:"Journey" duration: "251"
 * id:"231" title:"Livin' on a Prayer" artist:"Bon Jovi" duration: "249"
 * id:"764" title:"Sweet Child O' Mine" artist:"Guns N' Roses" duration: "356"
 * 482 317
 * 105 231
 * 231 105 764
 * 764 231
 *
 * @param fin Pointer to the input stream.
 * @param r Pointer to the radio.
 *
 * @return OK or ERROR
 */
Status radio_readFromFile(FILE* fin, Radio* r);

/**
 * @brief Returns a list of all the music in a radio
 *
 * @param r Pointer to the radio.
 *
 * @return A dinamic array of musics, which needs to be freed later. 
 * If error it returns NULL
 **/
Music** radio_getMusicList(Radio* radio)

#endif /* radio_H */
