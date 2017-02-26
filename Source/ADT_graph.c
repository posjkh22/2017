#include "ADT_llist.h"
#include "ADT_graph.h"
#include "ADT_queue.h"
#include "ADT_stack.h"
#include "math.h"

#define set_state_traversed(vertex)((vertex)->state = 1)
#define set_state_not_traversed(vertex)((vertex)->state = 0)
#define get_distance(from_vertex, to_vertex) \
	(sqrt( \
	 	(110.0) * ((from_vertex->loc.x) - (to_vertex->loc.x)) * \
		(110.0) * ((from_vertex->loc.x) - (to_vertex->loc.x)) + \
		(110.0) * (cosf((from_vertex->loc.x) / (180.0) * (3.14159))) * \
		((from_vertex->loc.y) - (to_vertex->loc.y)) * \
		(110.0) * (cosf((from_vertex->loc.x) / (180.0) * (3.14159))) * \
		((from_vertex->loc.y) - (to_vertex->loc.y)) )) 


bool g_bfs_gps(GRAPH* graph, int id){

	int vertex_loc = find_data3(graph->vertex_list, (void *)&id);
	if(vertex_loc == -1){
		printf(" could not find id(%d)\n", id);
		return false;
	}

	VERTEX *vertex_pos = (VERTEX*)get_data_at(graph->vertex_list, vertex_loc);
	set_state_traversed(vertex_pos);

	int i;
	ARC *arc_tmp;
	VERTEX *deq_vertex;
	
	QUEUE *queue = create_queue();

	enqueue(queue, (void *)vertex_pos);

	if(!vertex_pos)
		printf(" ERROR\n");

	/* if all data(vertex) is dequeue, stop */
	/* this means if deq_vertex is NULL, stop */

	while(1){

		deq_vertex = (VERTEX *)dequeue(queue);

		if(!deq_vertex)
			break;

		printf(" %d (%f %f)\n", deq_vertex->id, 
					deq_vertex->loc.x, deq_vertex->loc.y);
	
		vertex_pos = deq_vertex;


		vertex_pos->arc_list->pos = vertex_pos->arc_list->front;

		for( ; vertex_pos->arc_list->pos ; 
				vertex_pos->arc_list->pos = vertex_pos->arc_list->pos->next){

			arc_tmp = (ARC *)vertex_pos->arc_list->pos->data_ptr;

			if(arc_tmp->to_vertex->state)
				continue;

			/* queue data is vertex */
			if(!enqueue(queue, (void *)(arc_tmp->to_vertex)))
				continue;				

			set_state_traversed(arc_tmp->to_vertex);

		}

	}
	
	/* make all vertexes state not_traversed */	
	for(graph->vertex_list->pos = graph->vertex_list->front; 
			graph->vertex_list->pos; 
			graph->vertex_list->pos = graph->vertex_list->pos->next)
		set_state_not_traversed((VERTEX *)graph->vertex_list->pos->data_ptr);


}

bool g_dfs_gps(GRAPH* graph, int id){


	int vertex_loc = find_data3(graph->vertex_list, (void *)&id);
	if(vertex_loc == -1){
		printf(" could not find id(%d)\n", id);
		return false;
	}

	VERTEX *vertex_pos = (VERTEX*)get_data_at(graph->vertex_list, vertex_loc);
	set_state_traversed(vertex_pos);

	int i;
	ARC *arc_tmp;
	VERTEX *pop_vertex;
	
	STACK *stack = create_stack();

	push(stack, (void *)vertex_pos);

	if(!vertex_pos)
		printf(" ERROR\n");

	/* if all data(vertex) is pop, stop */
	/* this means if deq_vertex is NULL, stop */

	while(1){

		pop_vertex = (VERTEX *)pop(stack);

		if(!pop_vertex)
			break;

		printf(" %d (%f %f)\n", pop_vertex->id, 
					pop_vertex->loc.x, pop_vertex->loc.y);
	
		vertex_pos = pop_vertex;


		vertex_pos->arc_list->pos = vertex_pos->arc_list->front;

		for( ; vertex_pos->arc_list->pos ; 
			vertex_pos->arc_list->pos = vertex_pos->arc_list->pos->next){

			arc_tmp = (ARC *)vertex_pos->arc_list->pos->data_ptr;

			if(arc_tmp->to_vertex->state)
				continue;

			/* queue data is vertex */
			if(!push(stack, (void *)(arc_tmp->to_vertex)))
				continue;				

			set_state_traversed(arc_tmp->to_vertex);

		}

	}

	/* make all vertexes state not_traversed */	
	for(graph->vertex_list->pos = graph->vertex_list->front; 
			graph->vertex_list->pos; 
			graph->vertex_list->pos = graph->vertex_list->pos->next)
		set_state_not_traversed((VERTEX *)graph->vertex_list->pos->data_ptr);

}

/* [ find_data] find data by vertex */
/* [find_data2] find data by ARC->VERTEX->id */
/* [find_data2] find data by VERTEX->id */

int find_data2(LLIST* list, void* search_data) {
	list->pos = list->front;
	int cmp_result;
	int iter_i=0;

	while(list->pos != NULL) {

		ARC *tmp = (ARC *)list->pos->data_ptr;
		cmp_result = tmp->to_vertex->id - *(int *)search_data;
		if(cmp_result == 0)
			return iter_i;
		
		list->pos = list->pos->next;
		iter_i++;
	}
	return -1;
}

int find_data3(LLIST* list, void* search_data) {
	list->pos = list->front;
	int cmp_result;
	int iter_i=0;

	while(list->pos != NULL) {

		VERTEX *tmp = (VERTEX *)list->pos->data_ptr;
		cmp_result = tmp->id - *(int *)search_data;
		if(cmp_result == 0)
			return iter_i;
		
		list->pos = list->pos->next;
		iter_i++;
	}
	return -1;
}

GRAPH* create_graph_gps(){
	GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
	graph->vertex_list = create_list(compare_vertex, print_vertex);
	graph->size = 0;
	return graph;
}

// Inner Operations
int compare_vertex(void* x, void* y){
	VERTEX* left = (VERTEX*)x;
	VERTEX* right = (VERTEX*)y;

	return left->id - right->id;
}
void print_vertex(void* x){
	VERTEX* vertex = (VERTEX*)x;
	printf("vertex: %d\n", (int)vertex->id);
}
int compare_arc(void* x, void* y){
	int* left = (int*)x;
	ARC* right = (ARC*)y;

	return *left - right->to_vertex->id;
}
void print_arc(void* x){
	ARC* arc = (ARC*)x;
	printf("         -> : %d (%f %f [%fkm][traffic : %d])\n", (int)arc->to_vertex->id, 
						arc->to_vertex->loc.x, arc->to_vertex->loc.y,
						arc->distance, arc->traffic);
}

// Operations
bool g_insert_vertex_gps(GRAPH* graph, int id, float x, float y){
	int* idt = &id;
	// Creating Vertex
	VERTEX* new_vertex = (VERTEX*)malloc(sizeof(VERTEX));
	new_vertex->id = id;

	int vertex_loc = find_data(graph->vertex_list, new_vertex);
	if(vertex_loc != -1){
		free(new_vertex);
		printf(" error \n");
		return false;
	}

	new_vertex->loc.x = x;
	new_vertex->loc.y = y;
	new_vertex->arc_list = create_list(compare_arc, print_arc);

	
	if(add_node_at(graph->vertex_list, graph->vertex_list->count, new_vertex)){
		graph->size++;
		return true;
	}
	else
		return false;

}
bool g_delete_vertex(GRAPH* graph, int data){
	int* datat = &data;
	VERTEX* temp_vertex;
	ARC* temp_arc;
	int vertex_loc = find_data(graph->vertex_list, datat);
	if(vertex_loc == -1)
		return false;
	temp_vertex = (VERTEX*)get_data_at(graph->vertex_list, vertex_loc);

	while(temp_vertex->arc_list->count !=0) {
		ARC* reverse_arc =
		(ARC*)get_data_at(temp_vertex->arc_list, 0);
		int another_vertex_data =  reverse_arc->to_vertex->id;

		delete_arc(graph, data, another_vertex_data);
	}
	destroy_list(temp_vertex->arc_list);

	free(temp_vertex);
	del_node_at(graph->vertex_list, vertex_loc);
}
void print_vertex_all(GRAPH* graph){
	VERTEX* vertex_now;
	for(int iter_i = 0;
	iter_i < graph->vertex_list->count; iter_i++) {
		vertex_now = (VERTEX*)get_data_at(graph->vertex_list, iter_i);
		printf(" - ");
		print_vertex(vertex_now);
	}
}

bool g_insert_arc(GRAPH* graph, int from, int to, int traffic){

	// Searching from vertex
	VERTEX tmp_vertex1;
	tmp_vertex1.id = from;
	tmp_vertex1.arc_list = NULL;

	int tmp; 

	int vertex_loc = find_data(graph->vertex_list, &tmp_vertex1);
	if(vertex_loc == -1) {
		printf("from_vertex %d: not found\n", (int)from);
		return false; // error, there is no from vertex
	}

	// Getting a VERTEX with 'from' data
	VERTEX* from_vertex = (VERTEX*)get_data_at(graph->vertex_list,
	vertex_loc);

	// Searching to vertex
	VERTEX tmp_vertex2;
	tmp_vertex2.id = to;
	tmp_vertex2.arc_list = NULL;

	vertex_loc = find_data(graph->vertex_list, &tmp_vertex2);
	if(vertex_loc == -1) {
		printf("to_vertex %d: not found\n", (int)to);
		return false; // Nothing found
	}

	/* remove the same data */
	tmp = find_data2(from_vertex->arc_list, &to);
	if(tmp > -1){
		return false;
	}

	// Getting a VERTEX with 'from' data
	VERTEX* to_vertex = (VERTEX*)get_data_at(graph->vertex_list,
	vertex_loc);

	// Creating destination
	ARC* new_arc = (ARC*)malloc(sizeof(ARC));
	new_arc->to_vertex = to_vertex;
	new_arc->traffic = traffic;
	new_arc->current_weight = 0.0;

	// set distance information to arc->distance
	new_arc->distance = get_distance(from_vertex, to_vertex);

	// Inserting vertex into list
	return add_node_at(from_vertex->arc_list,
	from_vertex->arc_list->count, new_arc);
}

bool g_delete_arc(GRAPH* graph, int from, int to){
	// Searching from vertex
	VERTEX tmp_vertex1;
	int tempto = to;

	tmp_vertex1.id = from;
	tmp_vertex1.arc_list = NULL;

	int vertex_loc = find_data(graph->vertex_list, &tmp_vertex1);
	if(vertex_loc == -1) {
		printf("from_vertex %d: not found\n", (int)from);
		return false; // error, there is no from vertex
	}

	// Getting a VERTEX with 'from' data
	VERTEX* from_vertex = (VERTEX*)get_data_at(graph->vertex_list,
	vertex_loc);

	// Searching to vertex
	VERTEX tmp_vertex2;
	tmp_vertex2.id = from;
	tmp_vertex2.arc_list = NULL;

	vertex_loc = find_data(graph->vertex_list, &tmp_vertex2);
	if(vertex_loc == -1) {
		printf("to_vertex %d: not found\n", (int)tempto);
		return false; // Nothing found
	}

	int iter_i = 0;
	while(iter_i < from_vertex->arc_list->count) {
		ARC* to_arc = (ARC*)get_data_at(from_vertex
		->arc_list, iter_i);
		int todata = to_arc->to_vertex->id;
		if(compare_arc(&tempto, to_arc) == 0 )
			break;
	}

	// Inserting vertex into list
	return del_node_at(from_vertex->arc_list, iter_i);
}

bool insert_arc(GRAPH* graph, int from, int to, int traffic) {
	return g_insert_arc(graph, from, to, traffic)&&g_insert_arc(graph, to, from, traffic);
}
bool delete_arc(GRAPH* graph, int from, int to) {
	return g_delete_arc(graph, from, to)&&g_delete_arc(graph, to, from);
}

void print_arc_all(GRAPH* graph){
	VERTEX* vertex_now;
	ARC* arc_now;
	for(int iter_i = 0;
	iter_i < (graph->vertex_list->count); iter_i++) {
		vertex_now = (VERTEX*)get_data_at(graph->vertex_list, iter_i);
		print_vertex(vertex_now);
		for(int iter_j = 0;
		iter_j < (vertex_now->arc_list->count); iter_j++){
			arc_now = (ARC*)get_data_at(vertex_now->arc_list, iter_j);
			print_arc(arc_now);
		}
	}
}





