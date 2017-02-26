
bool initialize_Dijkstra(GRAPH *graph);

bool check_dijkstra_state(GRAPH *graph);

int compare(void *x, void *y);

bool find_shortest_way_all(GRAPH *graph, int id);

bool find_shortest_way(GRAPH *graph, int from, int to, char *argv[]);
