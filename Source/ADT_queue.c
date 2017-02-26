#include <stdio.h>
#include <stdlib.h>
#include "ADT_queue.h"


/* ==== create_queue() ==== */
QUEUE* create_queue() {
	QUEUE *queue = (QUEUE *)malloc(sizeof(QUEUE));

	if (queue) { // initialize queue
		queue->front = NULL;
		queue->rear = NULL;
		queue->count = 0;

		return queue;
	}
	else
		return NULL;
}

/* ==== enqueue() ==== */
bool enqueue(QUEUE *queue, void *in) {
	QUEUE_NODE *new_node;

	if(!in)
		return false;

	new_node = (QUEUE_NODE *)malloc(sizeof(QUEUE_NODE));

	if (new_node == NULL)
		return false;

	new_node->data_ptr = in;
	new_node->next = NULL;
	
	// first queue
	if (queue->count == 0) {
		queue->front = new_node;
		queue->rear = new_node;
		(queue->count)++;
	}
	// second, third... node
	else {
		queue->rear->next = new_node;
		(queue->count)++;
	}
	queue->rear = new_node;

	return true;
}



/* ==== dequeue() ==== */
void *dequeue(QUEUE *queue) {
	if (queue->count == 0) {
		return NULL;
	}
	else {
		void *item_ptr = queue->front->data_ptr;
		QUEUE_NODE *deleted_node = queue->front;

		if (queue->count == 1) {
			queue->front = NULL;
			queue->rear = NULL;
		}
		else {
			queue->front = queue->front->next;
		}
		(queue->count)--;
		free(deleted_node);
		
		return item_ptr;
	}
}


/* ==== queue_hook_front() ==== */
void *queue_hook_front(QUEUE *queue) {
	if (queue->count == 0)
		return NULL;
	else
		return queue->front->data_ptr;
}


/* ==== queue_hook_rear() ==== */
void *queue_hook_rear(QUEUE *queue) {
	if (queue->count == 0)
		return NULL;
	else
		return queue->rear->data_ptr;
}


/* ==== destroy_queue() ==== */
void destroy_queue(QUEUE *queue) {
	if (queue != NULL) {
		while (queue->count != 0) {
			int *del = (int *)(queue->front->data_ptr);
			printf("%d-th node is deleted\n", *del);
			free(queue->front->data_ptr);
			dequeue(queue);
		}
	}
}
