#include "ADT_llist.h"

/* ==== create_list() ==== */
LLIST *create_list (int (*cmp_func)(void *x, void *y), void (*print_func)(void *x)) {
	LLIST *list = (LLIST *)malloc(sizeof(LLIST));

	if (list) {
		list->front = NULL;
		list->rear = NULL;
		list->pos = NULL;
		list->cmp_func = cmp_func;
		list->print_func = print_func;
		list->count = 0;

		return list;
	}
	else
		return NULL;
}


/* ==== add_node_at() ==== */
bool add_node_at (LLIST *list, unsigned int index, void *data) {
	// over index
	if (index > list->count)
		return false;

	NODE *new_node;
	new_node = (NODE *)malloc(sizeof(NODE));

	if (!new_node)
		return false;

	new_node->data_ptr = data;
	new_node->next = NULL;

	if (list->count == 0) {	// insert initial
		list->front = new_node;
		list->rear = new_node;
		(list->count)++;

		return true;
	}

	int iter_i = 0;

	if (index == 0) {	// insert front
		new_node->next = list->front;
		list->front = new_node;
		(list->count)++;

		return true;
	}
	iter_i++;
	list->pos = list->front;

	while (iter_i != index) {	// move position
		list->pos = list->pos->next;
		iter_i++;
	}
	if (iter_i == list->count) {	// insert rear
		list->pos->next = new_node;
		list->rear = new_node;
		(list->count)++;

		return true;
	}
	else {	// insert mid
		new_node->next = list->pos->next;
		list->pos->next = new_node;
		(list->count)++;

		return true;
	}
}


/* ==== del_node_at() ==== */
bool del_node_at (LLIST *list, unsigned int index) {
	if (list->count == 0)
		return false;
	else if (index >= list->count)
		return false;

	if (list->count == 1) {
		free(list->front);
		list->front = NULL;
		list->rear = NULL;
		list->count = 0;

		return true;
	}

	int iter_i = 0;
	
	list->pos = list->front;
	NODE *pre = NULL;

	// move indexed position
	while (iter_i != index) {
		pre = list->pos;
		list->pos = list->pos->next;
		iter_i++;
	}

	// delete front
	if (index == 0) {
		list->front = list->pos->next;
		free(list->pos);
		list->pos = NULL;
		(list->count)--;

		return true;
	}

	// delete rear
	if (index == (list->count - 1)) {
		list->rear = pre;
		pre->next = NULL;
		free(list->pos);
		list->pos = NULL;
		(list->count)--;

		return true;
	}

	// delete mid
	else {
		pre->next = list->pos->next;
		free(list->pos);
		list->pos = NULL;
		(list->count)--;

		return true;
	}

	return false;
}


/* ==== get_data_at() ==== */
void *get_data_at (LLIST *list, unsigned int index) {
	if (index >= list->count)
		return NULL;

	list->pos = list->front;
	int iter_i = 0;

	while (list->pos != NULL) {
		if (iter_i == index)
			return list->pos->data_ptr;

		list->pos = list->pos->next;
		iter_i++;
	}

	return NULL;
}


/* ==== find_data() ==== */
int find_data (LLIST *list, void *search_data) {
	list->pos = list->front;
	int cmp_result, left, right;
	int iter_i = 0;

	while (list->pos != NULL) {
		cmp_result = (*(list->cmp_func))(list->pos->data_ptr, search_data);
		if (cmp_result == 0)	// found data
			return iter_i;
		list->pos = list->pos->next;
		iter_i++;
	}

	return -1;
}


/* ==== print_all ==== */
void print_all (LLIST *list, NODE *from_front) {
	NODE *pos = from_front;

	while (pos != NULL) {
		(*(list->print_func))(pos->data_ptr);
		pos = pos->next;
	}
}


/* ==== copy_list ==== */
LLIST *copy_list (LLIST *list) {
	LLIST *copy_list = create_list(list->cmp_func, list->print_func);	// perfect copy
	
	if (!copy_list)	// create error
		return NULL;
	if (list->count == 0)	// zero node
		return NULL;

	int iter_i = 0;
	list->pos = list->front;

	while (iter_i < list->count) {
		add_node_at (copy_list, iter_i, list->pos->data_ptr);
		list->pos = list->pos->next;
		(iter_i)++;
	}

	return copy_list;
}
