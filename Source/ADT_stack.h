#ifndef ADT_STACK
#define ADT_STACK

#include <stdlib.h>

/* ==== Stack Node ==== */

#ifndef ADT_LLIST
typedef struct node {
	void *data_ptr;
	struct node *link;
} STACK_NODE;
#endif

#ifdef ADT_LLIST
typedef struct snode {
	void *data_ptr;
	struct node *link;
} STACK_NODE;
#endif

/* ==== Stack ADT ==== */
typedef struct {
	int count;
	STACK_NODE *top;
} STACK;

/* ==== Interface ==== */
STACK *create_stack();
bool push(STACK *stack, void *in);
void *pop(STACK *stack);
void fill_space(int size);
#endif
