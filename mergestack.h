#ifndef MERGESTACK_H_
#define MERGESTACK_H_

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Typedef for a function pointer to print a stack element at stream
 **/
typedef int (*P_mergestack_cmp)(const void *e1, const void *e2);

#endif