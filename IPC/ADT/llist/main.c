#include <stdio.h>
#include "ADT_llist.h"

int compare1 (void *x, void *y) {
	return *((int *)x) - *((int *)y);
}

void print1 (void *x) {
	int *xp = (int *)x;
	printf(" - int data %d\n", *xp);
}

int main() {
	int i;
	LLIST *list = create_list(compare1, print1);

	int foo1 = 100;
	int foo2 = 200;
	int foo3 = 300;
	int foo4 = 400;
	int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	// error
	if (!add_node_at(list, 1, &foo1))
		printf("list is empty: index %d is not allowed\n", 1);

	// insert front
	if (!add_node_at(list, 0, &foo1))
		printf("data insertion failed on empty list\n");
	else
		printf("data insertion OK on empty list: %d\n", foo1);

	// insert rear
	if (!add_node_at(list, list->count, &foo2))
		printf("data insertion failed on rear\n");
	else
		printf("data insertion OK on rear node: %d\n", foo2);

	printf("10 data insertion:\n");
	for (i = 0; i < 10; i++) {
		if (!add_node_at(list, i, &data[i]))
			printf(" - add faild at %d\n", i);
		else
			printf(" - add OK at %d: %d\n", i, data[i]);
	}

	// copy list
	LLIST *list2 = copy_list(list);
	int count = list2->count;

	printf("copied list2: ");
	for (i = 0; i < count; i++)
		printf("%d ", *(int *)get_data_at(list2, i));
	printf("\n");

	// insert rear
	if(!add_node_at(list, list->count, &foo3))
		printf("data insertion failed on rear\n");
	else
		printf("data insertion OK on rear node: %d\n", foo3);

	// insert front
	if (!add_node_at(list, 0, &foo4))
		printf("data insertion failed on front\n");
	else
		printf("data insertion OK on front: %d\n", foo4);

	// print list all
	printf("Print all iterative: \n");
	print_all(list, list->front);

	// delete front
	if (!del_node_at(list, 0))
		printf("data deletion failed on index 0\n");
	else
		printf("data deletion success on index 0\n");

	printf("Print all iterativw:\n");
	print_all(list, list->front);

	// delete rear
	if (!del_node_at(list, list->count - 1))
		printf("data deletion failed on rear\n");
	else
		printf("data deletion success on rear\n");

	// delete mid
	if (!del_node_at(list, 4))
		printf("data deletion failed on index 4\n");
	else
		printf("data deletion success on index 4\n");

	printf("Current list size: %d\n", list->count);
	printf("Print all iterative:\n");
	print_all(list, list->front);

	int found;
	int search = 200;
	int *searched_ptr;
	found = find_data(list, &search);
	searched_ptr = (int *)get_data_at(list, found);

	if (found != -1)
		printf("found %d at index %d\n", *searched_ptr, found);

	search = 5;
	found = find_data(list, &search);
	searched_ptr = (int *)get_data_at(list, found);

	if (found != -1)
		printf("found %d at index %d\n", *searched_ptr, found);

	return 0;
}
