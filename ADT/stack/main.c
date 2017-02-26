#include <stdio.h>
#include "ADT_stack.h"

int main() {
	// stack creation
	STACK *stack_ptr;
	stack_ptr = create_stack();

	int i, j, k;

	// +->pushed 100
	i = 100;

	if (!push(stack_ptr, &i)) {
		printf("Stack push error!\n");
		return -1;
	}
	else {
		fill_space(stack_ptr->count);
		printf(" +->pushed: %d\n", i);
	}

	// +->pushed 200
	j = 200;

	if (!push(stack_ptr, &j)) {
			printf("Stack push error!\n");
			return -1;
	}
	else {
		fill_space(stack_ptr->count);
		printf(" +->pushed: %d\n", j);
	}

	// +->pushed 300
	k = 300;

	if (!push(stack_ptr, &k)) {
			printf("Stack push error!\n");
			return -1;
	}
	else {
		fill_space(stack_ptr->count);
		printf(" +->pushed: %d\n", k);
	}

	// puch loop with array data
	int idx;
	int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	for (idx = 0; idx < 10; idx++) {
		if (!push(stack_ptr, data+idx)) {
			printf("Stack push error!\n");
			return -1;
		}
		else {
			fill_space(stack_ptr->count);
			printf(" +->puched: %d\n", data[idx]);
		}
	}

	// loop pop until empty
	printf(" ***** Pop start ***** \n");
	while (stack_ptr->count != 0) {
		fill_space(stack_ptr->count);
		int *data_popped = (int *)pop(stack_ptr);
		printf(" <- popped: %d\n", *data_popped);
	}

	pop(stack_ptr);

	return 0;
}
