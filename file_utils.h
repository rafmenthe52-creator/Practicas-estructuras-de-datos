#ifndef _FILE_UTILS_H
#define _FILE_UTILS_H

#include "types.h"


/* generic function type to process an element */
typedef void (*process_element)(const void *element);


//---------------------------------------------------------
// functions to manage pointer types
//---------------------------------------------------------

// functions to manage pointer to int
int *int_init(int a);
void *int_copy (const void *a);
int int_cmp (const void *c1, const void *c2); 
void int_free (void *a);
int int_print(FILE *pf, const void *a); 

// funcions to manage pointer to char
char *char_init (char a);
void *char_copy (const void *a); 
int char_cmp (const void *c1, const void *c2); 
void char_free (void *a); 
int char_print (FILE *pf, const void *a); 

// functions to manage pointer to float
float *float_init (float a);
void *float_copy (const void *a); 
int float_cmp (const void *c1, const void *c2); 
void float_free (void *a); 
int float_print (FILE *pf, const void *a); 

// functions to manage pointer to string (noy very interesting)
void *string_copy (const void *src); 
int string_cmp (const void *c1, const void *c2); 
void string_free (void *str); 
int string_print (FILE *pf, const void *str); 


#endif
