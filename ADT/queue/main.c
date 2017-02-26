#include <stdio.h>
#include "ADT_queue.h"


typedef struct student {
	int id;
	int score;
} STD;

#define STD_N 20

int main() {
	int i, tmp;
	STD *c[STD_N];

	// create queue
	QUEUE *queue;
	queue = create_queue();

	// std memeoy allocate
	for (i = 0; i < STD_N; i++) {
		c[i] = (STD *)malloc(sizeof(STD));
	}

	for (i = 0; i < STD_N; i++) {
		c[i]->id = i;
		c[i]->score = i+1000;
	}

	for (i = 0; i < STD_N; i++) {
		if (enqueue(queue, &(c[i]->id))) {
			printf("Enqueue: %d\n", c[i]->id);
		}
		else {
			printf("Enqueue failed\n");
			return -1;
		}
	}

	// Data extract
	while (queue->count != 0) {
		tmp = *(int *)dequeue(queue);
		printf("Dequeue: %d\n", tmp);
	}

	// Re-insert
	for (i = 0; i < STD_N; i++) {
		if (enqueue(queue, &(c[i]->id))) {
			printf("Enqueue: %d\n", c[i]->id);
		}
		else {
			printf("Enqueue failed\n");
			return -1;
		}
	}

	// destroy all queue
	destroy_queue(queue);
	return 0;
}
