#include <math.h>
#include <string.h>
#include "ADT_graph.h"
#include "ADT_heap.h"
#include "ADT_llist.h"
#include "ADT_Dijkstra.h"
#include "unistd.h"


#define HEAP_SIZE 50000
#define MAX_VERTEX 3500
#define DIJKSTRA_MAX_VALUE 9999

/* for consideration of TRAFFIC factor */

/*
int dijkstra_state[MAX_VERTEX];
float dijkstra_value[MAX_VERTEX];
*/


int *dijkstra_state;
float *dijkstra_value;

int *path;


//#define TRAFFIC
//#define DEBUG

#define set_state_set(vertex)(dijkstra_state[(vertex)->id] = 1)
#define set_state_unset(vertex)(dijkstra_state[(vertex)->id] = 0)
#define get_state(vertex)(dijkstra_state[(vertex)->id])
#define dijkstra_value_from_vertex(vertex)(dijkstra_value[(vertex)->id])



#define traffic_factor(traffic)((float)(sqrt(traffic)+1) * 0.005 )


float current_weight = 0.0;


bool initialize_Dijkstra(GRAPH *graph, int id){

	int i;
	int j;

	dijkstra_state = (int *)malloc(sizeof(int) * (graph->size+1));
	dijkstra_value = (float *)malloc(sizeof(float) * (graph->size+1));
	path = (int *)malloc(sizeof(int) * (graph->size+1) * (graph->size+1));


	for(i = 1; i < graph->size+1; i++){

		dijkstra_value[i] = DIJKSTRA_MAX_VALUE;
		dijkstra_state[i] = 0;
	
	}

	for(i = 1; i < graph->size+1; i++){

		for(j = 1; j < graph->size+1; j++){

			//path[i][j] = DIJKSTRA_MAX_VALUE;
			path[i * graph->size +j] = DIJKSTRA_MAX_VALUE;

		}
	}

	for(i = 1; i < graph->size+1; i++){

		//path[i][0] = id;
		path[i * graph->size +0] = id;
		//path[i][graph->size-1] = i;
		path[i *graph->size + graph->size-1] = i;

	}

}



bool add_path(VERTEX *from, VERTEX *to, GRAPH *graph, int count){

	int i = 0;
	for(i = 0; i < graph->size-1; i++){
		
		//path[to->id][i] = path[from->id][i];
		path[to->id * graph->size +i] = path[from->id *graph->size +i];

	}
	
	path[to->id * graph->size + count] = from->id;

}

bool check_dijkstra_state(GRAPH *graph){

	int i;
	int check_sum = 0;

	for(i = 1; i < graph->size+1; i++){
	
		if(dijkstra_state[i] == 1)
			check_sum++;	
	}

	if(check_sum == graph->size){
		return true;
	}

	else{
		return false;
	}
}

int arc_compare(void *x, void *y){

	//ARC->distance compare

	ARC *px = (ARC *)x;
	ARC *py = (ARC *)y;

	if(px->current_weight > py->current_weight)
		return 1;

	else if(px->current_weight < py->current_weight)
		return -1;

	else
		0;

}





bool find_shortest_way_all(GRAPH *graph, int id){

	void *data_out;	
	ARC *arc_tmp;
	int i;
	int j;	
	int count;

	initialize_Dijkstra(graph, id);

	int vertex_loc = find_data3(graph->vertex_list, (void *)&id);
	if(vertex_loc == -1){
		printf(" could not find id(%d)\n", id);
		return false;
	}

	
	VERTEX *vertex_pos = (VERTEX*)get_data_at(graph->vertex_list, vertex_loc);

	HEAP *heap = heapCreate(HEAP_SIZE, arc_compare);

	/* initialize current_weight */
	current_weight = 0;

	/* first self value = 0 */
	dijkstra_value[vertex_pos->id] = 0;


	count = 0;

	while(1){


		/* for no reback */
		set_state_set(vertex_pos);

		/* end condition */
		if(check_dijkstra_state(graph))
			break;



		vertex_pos->arc_list->pos = vertex_pos->arc_list->front;
	
		for( ; vertex_pos->arc_list->pos ; 
				vertex_pos->arc_list->pos = vertex_pos->arc_list->pos->next){

		
			arc_tmp = (ARC *)vertex_pos->arc_list->pos->data_ptr;

			if(get_state(arc_tmp->to_vertex) == 1)		
				continue;


			/* heap data is ARC */
			/* but, compare data is arc->distance + current_weight */
			/* From the heapDelete data_out ARC, current_weight is determined */

			#ifdef TRAFFIC
			arc_tmp->current_weight
				 = arc_tmp->distance + traffic_factor(arc_tmp->traffic) + current_weight;
			#endif

			#ifndef TRAFFIC
			arc_tmp->current_weight
				 = arc_tmp->distance + current_weight;
			#endif

			if(heapInsert(heap, (void *)(arc_tmp))){

				#ifdef DEBUG
				printf(" prior id %d\n", vertex_pos->id);
				printf(" Insert Heap %d\n", arc_tmp->to_vertex->id);		
				printf(" value prior : %f\n", dijkstra_value[arc_tmp->to_vertex->id]);	
				#endif	

				if(dijkstra_value[arc_tmp->to_vertex->id] 
						> arc_tmp->current_weight){

					dijkstra_value[arc_tmp->to_vertex->id] 
						= arc_tmp->current_weight;

					#ifdef DEBUG
					printf(" value changed : %f\n", dijkstra_value[arc_tmp->to_vertex->id]);	
					printf(" value changed id : %d\n", arc_tmp->to_vertex->id);	
					#endif
				
					/* make path array */
					add_path(vertex_pos, arc_tmp->to_vertex, graph, count);				
		
				
					#ifdef DEBUG
					for( j = 0 ; j < graph->size; j++){
							//if(path[arc_tmp->to_vertex->id][j] != DIJKSTRA_MAX_VALUE)
							if(path[arc_tmp->to_vertex->id * graph->size + j] != DIJKSTRA_MAX_VALUE)
								printf(" ->[%d]", path[arc_tmp->to_vertex->id *graph->size + j]);
					}
					printf("\n");
					#endif
					
				}

				/* no consideration for heap algorithms */
				/* else case can't have higher priority */
					

			}

			else{
				#ifdef DEBUG
				printf(" Insert Fail %d \n", arc_tmp->to_vertex->id);
				#endif
			}			


		}
	

		/* release (for no reback) */

		while(1){

			if(!heapDelete(heap, &data_out)){
				printf(" Heap Delete Error \n");
			}
			
			
			vertex_pos = ((ARC *)data_out)->to_vertex;

			//sleep(1);
			if(!dijkstra_state[vertex_pos->id]){
				#ifdef DEBUG
				printf(" out Heap : %d\n", vertex_pos->id);
				#endif
				break;				
			}
		}


		current_weight = dijkstra_value[vertex_pos->id];	

		count++;

	}

	#ifdef DEBUG
	printf(" TABLE\n");

	for( i = 1 ; i < graph->size+1; i++){
		printf(" [%d] %f\n", i, dijkstra_value[i]);
		printf(" [%d] %d\n", i, dijkstra_state[i]);
	}

	/* print All shortest path from id */
	for( i = 1 ; i < graph->size+1; i++){

		for( j = 0 ; j < graph->size; j++){
			//if(path[i][j] != DIJKSTRA_MAX_VALUE)
			if(path[i * graph->size + j] != DIJKSTRA_MAX_VALUE)
				printf(" ->[%d]", path[i * graph->size + j]);
				//printf(" ->[%d]", path[i][j]);
		}
		printf("\n");
	}
	#endif

	return true;
}



bool find_shortest_way(GRAPH *graph, int from, int to, char *argv[]){

	int j;
	int x;
	int y;
	int tmp;


	char shortest_way[30];

	if(!strcmp(argv[3], "multi"))
		strcpy(shortest_way, "shortest_way1.out");

	else if(!strcmp(argv[3], "multi2"))
		strcpy(shortest_way, "shortest_way2.out");

	else if(!strcmp(argv[3], "multi3"))
		strcpy(shortest_way, "shortest_way3.out");

	FILE *fout = fopen(shortest_way, "w");

	find_shortest_way_all(graph, from);
	

	for(j = 0; j <graph->size; j++){
		
		//if(path[to][j] != DIJKSTRA_MAX_VALUE)
		if(path[to *graph->size * j] != DIJKSTRA_MAX_VALUE)
			printf(" -> %d", path[to * graph->size +j]);
			//printf(" -> %d", path[to][j]);

	}

	#ifdef TRAFFIC
	printf("[TRAFFIC]\n");
	#endif		

	#ifndef TRAFFIC
	printf("\n");
	#endif		
	for(j = 0; j <graph->size; j++){

		//while(path[to][j] == DIJKSTRA_MAX_VALUE){
		while(path[to *graph->size +j] == DIJKSTRA_MAX_VALUE){
			j++;
		}
		
		x = path[to * graph->size +j];
		//x = path[to][j];

		tmp = j;	

		for(j = tmp+1; j < graph->size; j++){
			//if(path[to][j] != DIJKSTRA_MAX_VALUE){
			if(path[to *graph->size +j] != DIJKSTRA_MAX_VALUE){
				 y = path[to * graph->size +j];
				 //y = path[to][j];
				 break;
			}
		}

		j = tmp;
	
		if( x == y)
			break;

		fprintf(fout, "%d %d\n",x, y);
	}

	fclose(fout);

}
