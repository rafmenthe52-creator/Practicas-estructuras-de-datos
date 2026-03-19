#include "queue.h"
#include <stdlib.h>

struct _Queue{
  void *data[MAX_QUEUE];  /*pointer to Data inside queue. the data is stored as a pointer*/
  void **front;   /*Pointer to *data[x]*/
  void **rear;    /*Pointer to *data[x]*/
};

/*Private funtions*/
/**
 * @brief Checks whether the queue is full or not.
 *
 * @param q A pointer to the queue.
 *
 * @return TRUE if the queue is full, FALSE otherwise.
 */
static Bool queue_isFull(const Queue *q){
  if(!q) return FALSE;

  return (q->rear == q->front) ? TRUE : FALSE;
}

/*Public funtions*/

Queue *queue_new() {
  Queue *q;
  q=(Queue*)malloc(sizeof(Queue));
  if (!q) return NULL;

  for (int i = 0; i < MAX_QUEUE; i++) q->data[i] = NULL;
  q->front = &q->data[INIT_FRONT];
  q->rear  = &q->data[INIT_REAR];

  return q;
}

void queue_free(Queue *q){
  if(!q){
    return;
  }

  free(q);
}

Bool queue_isEmpty(const Queue *q){
  int rear_idx, prev_rear_idx;

  if (!q) return FALSE;  

  rear_idx = (int)(q->rear - q->data);
  prev_rear_idx = (rear_idx - 1 + MAX_QUEUE) % MAX_QUEUE;

  return (q->front == &q->data[prev_rear_idx]) ? TRUE : FALSE;
}

Status queue_push(Queue *q, void *ele){
  if (!q || !ele || queue_isFull(q)==TRUE) return ERROR;

  /*Add the element to the rear*/
  *q->rear = ele;

  /*Increment rear by one*/
  q->rear = q->data + (q->rear+1 - q->data) % MAX_QUEUE;

  return OK;
}

void *queue_pop(Queue *q){
  void *ele;

  if(!q || queue_isEmpty(q)==TRUE) return NULL;

  /*Copy front data to ele*/
  ele=*q->front;

  /*Increment front by 1*/
  q->front = q->data + (q->front+1 - q->data) % MAX_QUEUE;


  return ele;
}

void *queue_getFront(const Queue *q){
  int front_idx;

  if(!q || queue_isEmpty(q)==TRUE) return NULL;

  front_idx = (q->front - q->data + 1) % MAX_QUEUE;

  return q->data[front_idx];
}

void *queue_getBack(const Queue *q){
  int rear_idx;

  if(!q || queue_isEmpty(q)==TRUE) return NULL;

  rear_idx = (q->rear - q->data - 1 + MAX_QUEUE) % MAX_QUEUE;

  return q->data[rear_idx];
}

size_t queue_size(const Queue *q){
  if(!q) return QUEUE_NOT_FOUND;

  if(queue_isEmpty(q)==TRUE){
    return SIZE_0;
  }

  return (q->front<q->rear) ? q->rear-q->front : (q->rear+MAX_QUEUE)-q->front;
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f){
  int count = 0, idx;
  
  if(!fp || !q || !f){
    return INVALID_INT;
  }

  if(queue_isEmpty(q)==TRUE) return INVALID_INT;

  idx = (int)((q->front - q->data + 1) % MAX_QUEUE);
  while(idx != (int)(q->rear - q->data)){
    count += f(fp, q->data[idx]);
    if(count < 0) return INVALID_INT;

    count += fprintf(fp, "\n");
    if(count < 0) return INVALID_INT;

    idx = (idx + 1) % MAX_QUEUE;
  }

  return count;
}