/**
 * @file types.h
 * @author Profesores EDAT
 * @date February 2026
 * @brief ADT Boolean and Status
 *
 * @details Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by @.
 * 
 * @see 
 */

#ifndef TYPES_H_
#define TYPES_H_

/**
 * @brief ADT Boolean
 */
typedef enum {
    ERROR=-1, /*!< For error checking purposes*/
    FALSE=0, /*!< False value */
    TRUE=1  /*!< True value  */
} Bool;

/** 
 * @brief ADT Status
 */
typedef enum {
    ERROR=0, /*!< To codify an ERROR output */
    OK=1,     /*!< OK output */
    FINISHED=2  /*!< Process FINISHED */
} Status;

/* Common Magic Numbers */
#define INVALID_ID (-1)
#define INVALID_INDEX (-1)
#define QUEUE_NOT_FOUND (-1)
#define INIT_VALUE 0
#define SECONDS_PER_MINUTE 60
#define POSITION_NOT_FOUND (-1)

#endif /* TYPES_H_ */
