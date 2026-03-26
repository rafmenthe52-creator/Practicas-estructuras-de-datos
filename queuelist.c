#include "queue.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

struct _Queue{
    List *pl;
};


Queue* queue_new(){
    Queue* queue = NULL;

    queue = (Queue*)malloc(1*sizeof(Queue));
    if(!queue) return NULL;

    queue->pl=list_new();
    if(!queue->pl) free(queue);

    return queue;
}

void queue_free(Queue* queue){
    if(!queue) return;

    list_free(queue->pl);

    free(queue);

    return;
}

Bool queue_isEmpty(const Queue *q){
    if(!q) return TRUE;

    return list_isEmpty(q->pl);
}

Status queue_push(Queue* q, void* ele){
    if(!q||!ele) return ERROR;

    return list_pushBack(q->pl, ele);
}

void *queue_pop(Queue *q){
    if(!q) return NULL;

    return list_popFront(q->pl);
}

void* queue_getFront(const Queue* q){
    if(!q) return NULL;

    return list_getFront(q->pl);
}

void *queue_getBack(const Queue *q){
    if(!q) return NULL;

    return list_getBack(q->pl);
}

size_t queue_size(const Queue *q){
    if(!q) return SIZE_0;

    return list_size(q->pl);
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f){
    if(!fp || !q || !f) return INVALID_INT;
    
    return list_print(fp, q->pl, f);
}