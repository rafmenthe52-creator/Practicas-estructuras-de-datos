#include "queue.h"

struct _Queue{
  void *data[MAX_QUEUE];  /*pointer to Data inside queue. the data is stored as a pointer*/
  void **front;   /*Pointer to *data[x]*/
  void **rear;    /*Pointer to *data[x]*/
};

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
  void **prev_rear;

  if(!q){
    return FALSE; /*I decided to return false in this case, but i could have used Bool ERROR, which i created for purposes like this one*/
  }

  prev_rear = q->data + (q->rear+1 - q->data) % MAX_QUEUE;

  return (q->front == prev_rear) ? TRUE : FALSE;
}

Status queue_push(Queue *q, void *ele){
  void **next_rear;

  if (!q || !ele) return ERROR;

  /*Add the element to the rear*/
  *q->rear = ele;

  /*Increment rear by one*/
  q->rear = q->data + (q->rear+1 - q->data) % MAX_QUEUE;

  return OK;
}

void *queue_pop(Queue *q){
  void **next_front, *ele;

  if(!q || queue_isEmpty(q)==TRUE) return NULL;

  /*Copy front data to ele*/
  ele=*q->front;

  /*Increment front by 1*/
  q->front = q->data + (q->front+1 - q->data) % MAX_QUEUE;


  return ele;
}

void *queue_getFront(const Queue *q){
  if(!q) return NULL;

  return q->front;
}

void *queue_getBack(const Queue *q){
  if(!q) return NULL;

  return q->rear;
}/**
 * @brief This function returns the size of a queue. Note that the function returns
 * 0 if it is called with a NULL pointer. Time complexity: O(1).
 *
 * @param q A pointer to the queue.
 *
 * @return The queue size, 0 in case of error. 
 */
size_t queue_size(const Queue *q){
  if(!q) return QUEUE_NOT_FOUND;
}

