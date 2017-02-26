#include <stdio.h>
#include <stdlib.h>
#include "ADT_stack.h"


/* ==== create_stack() ==== */
STACK *create_stack() {
	STACK *stack = (STACK *)malloc(sizeof(STACK));

	if (stack == NULL) {
		printf("Stack dynamic allocation error!\n");
		return NULL;
	}
	stack->count = 0;	// stack is empty
	stack->top = NULL;	// stack initialize

	return stack;
}

/* ==== push() ==== */
bool push(STACK *stack, void *in) {
	STACK_NODE *new_node = (STACK_NODE *)malloc(sizeof(STACK_NODE));

	if (new_node == NULL) {
		printf("Stack's node dynamic allocation error!\n");
		return false;
	}

	new_node->data_ptr = in;
	new_node->link = stack->top;
	stack->top = new_node;
	(stack->count)++;

	return true;
}

/* ==== pop() ==== */
void *pop(STACK *stack) {
	if(stack->count == 0) {
		#ifdef DEBUG
		printf("Stack is empty!\n");
		#endif
		return NULL;
	}
	else {
		STACK_NODE *temp = stack->top;
		void *data_out = stack->top->data_ptr;

		stack->top = stack->top->link;
		free(temp);
		(stack->count)--;

		return data_out;
	}
}

/* ==== fill_space ==== */
void fill_space(int size) {
	int j;

	for (j = 0; j < size; j++) {
		printf(" ");
	}
}
