
#include <stdio.h>
#include <stdlib.h>
#include "ADT_llist.h"

#define MAX_GRAPH_SIZE 10000

typedef struct position{
	float x;
	float y;
}POSITION;

// Vertex node
typedef struct vertex {
	POSITION loc;
	int id;
	int state;
	LLIST* arc_list;
} VERTEX;

// Arc node
typedef struct arc {
	float distance;
	int traffic;
	struct vertex* to_vertex;
	float current_weight;
} ARC;

// GRAPH
typedef struct {
	LLIST* vertex_list;
	int size;
} GRAPH;

// Inner Operations;
int compare_vertex(void* x, void* y);
void print_vertex(void* x);
int compare_arc(void* x, void* y);
void print_arc(void* x);

// Operations;
GRAPH* create_graph_gps();
bool g_insert_vertex_gps(GRAPH* graph, int id, float x, float y);
bool g_delete_vertex(GRAPH* graph, int data);
void print_vertex_all(GRAPH* graph);

bool g_insert_arc(GRAPH* graph, int from, int to, int traffic);
bool g_delete_arc(GRAPH* graph, int from, int to);
bool insert_arc(GRAPH* graph, int from, int to, int traffic);
bool delete_arc(GRAPH* graph, int from, int to);
void print_arc_all(GRAPH* graph);
int find_data2(LLIST* list, void* search_data);
int find_data3(LLIST* list, void* search_data);

bool g_bfs_gps(GRAPH* graph, int id);
bool g_dfs_gps(GRAPH* graph, int id);





