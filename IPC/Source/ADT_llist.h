#ifndef ADT_LLIST
#define ADT_LLIST

#include <stdio.h>
#include <stdlib.h>

// List Node
typedef struct node {
	void* data_ptr;
	struct node* next;
} NODE;

// List
typedef struct {
	int count;
	NODE* front;
	NODE* rear;
	NODE* pos;
	int (*cmp_func)(void* x, void* y);
	void (*print_func)(void* x);
} LLIST;

//Operations
LLIST* create_list( int (*cmp_func)(void* x, void* y),
	void (*print_func)(void* x));
bool add_node_at(LLIST* list, unsigned int index, void* data);
bool del_node_at(LLIST* list, unsigned int index);
void* get_data_at(LLIST* list, unsigned int index);
int find_data(LLIST* list, void* search_data);
LLIST* copy_list(LLIST* list);
void print_all(LLIST* list, NODE* from_front);
void destroy_list(LLIST* list);

#endif
