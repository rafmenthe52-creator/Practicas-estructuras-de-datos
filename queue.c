#include "queue.h"
#include <stdlib.h>

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
  Queue *qAux;

  qAux=(Queue*)(q);

  if(!q){
    return FALSE; /*I decided to return false in this case*/
  }

  prev_rear = qAux->data + (qAux->rear+1 - qAux->data) % MAX_QUEUE;

  return (qAux->front == prev_rear) ? TRUE : FALSE;
}

Status queue_push(Queue *q, void *ele){
  if (!q || !ele) return ERROR;

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
  void* ele;
  
  if(!q) return NULL;

  ele= q->front - (MAX_QUEUE+ q->front-1 -q->data) % MAX_QUEUE;

  return ele;
}

void *queue_getBack(const Queue *q){
  if(!q) return NULL;

  return q->rear;
}

size_t queue_size(const Queue *q){
  if(!q) return QUEUE_NOT_FOUND;

  if(queue_isEmpty(q)==TRUE){
    return SIZE_0;
  }

  return (q->front<q->rear) ? q->rear-q->front : (q->rear+MAX_QUEUE)-q->front;
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f){
  Queue *qIn;
  void *ele;
  int count = 0, i;
  
  if(!fp || !q || !f){
    return INVALID_INT;
  }

  if(queue_isEmpty(q)==TRUE) return INVALID_INT;

  if(q->front<q->rear){
    for(i=((q->front-q->data)%MAX_QUEUE); i<((q->rear-q->data)%MAX_QUEUE); i++){
      count+=f(fp, q->data[i]);
      fprintf(fp, "\n");
    }
  }else{
    for(i=((q->front-q->data)%MAX_QUEUE); i<((q->rear-q->data)%MAX_QUEUE); i++){
      count+=f(fp, q->data[i]);
      fprintf(fp, "\n");
      if(i=MAX_QUEUE-1) i=0;
    }
  }  

  return count;
}