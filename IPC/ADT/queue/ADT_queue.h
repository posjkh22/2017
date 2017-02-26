#ifndef ADT_QUEUE
#define ADT_QUEUE

#include <stdio.h>
#include <stdlib.h>

/*
typedef int bool;
#define true 1
#define false 0
*/

/* ==== Queue Node ==== */
typedef struct node {
	void *data_ptr;
	struct node *next;
} QUEUE_NODE;


/* ==== Queue ==== */
typedef struct queue{
	int count;
	QUEUE_NODE *front;
	QUEUE_NODE *rear;
} QUEUE;


/* ==== define function ==== */
QUEUE* create_queue();
bool enqueue (QUEUE *queue, void *in);
void *dequeue (QUEUE *queue);

void *queue_hook_front (QUEUE *queue);
void *queue_hook_rear (QUEUE *queue);
void destroy_queue (QUEUE *queue);

#endif
