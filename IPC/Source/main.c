// ADT Graph

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "ADT_llist.h"
#include "ADT_graph.h"
#include "ADT_Dijkstra.h"
#include "ADT_create_Map.h"


/*				****  note  ****						*/
/* DATE : 2017-01-24									*/
/* if input location data have circular connections, 	*/
/* the problem occurs in ADT_Dijkstra.c					*/

/* How to ues DEFINE in main ? */


/* DATE : 2017-02-03									*/
/* use PIPE for changing traffic data 					*/

//#define DEBUG


char map_loc_data[30] = "map_loc_data.in";
char map_cnt_data[30] = "map_cnt_data.in";
char shortest_way[30];


bool g_generate_crosspoint(FILE *fin_loc){

	create_map_html(fin_loc, NULL, NULL);

}

bool g_generate_line(FILE *fin_loc, FILE *fin_cnt){

	create_map_html(fin_loc, fin_cnt, NULL);

}

bool g_generate_shortest_path(GRAPH *graph, int from, int to, char *argv[]){

	FILE *fin_loc = fopen(map_loc_data, "r");
	FILE *fin_cnt = fopen(map_cnt_data, "r");

	find_shortest_way(graph, from, to, argv);
	
	FILE *fin_shortest_way = fopen(shortest_way, "r");

	if( to < 52)
		create_map_html(fin_loc, fin_cnt, fin_shortest_way);

	fclose(fin_loc);
	fclose(fin_cnt);
	fclose(fin_shortest_way);

}


int main(int argc, char *argv[]) {

	int i = 0;

	int id;
	int target;
	float data_x;
	float data_y;	

	if(argc == 4){
	
		if(!strcmp(argv[3], "multi")){
			strcpy(map_loc_data, "map_loc_multi_data.in");
			strcpy(map_cnt_data, "map_cnt_multi_data.in");
			strcpy(shortest_way, "./shortest_way1.out");
		}
	
		else if(!strcmp(argv[3], "multi2")){
			strcpy(map_loc_data, "map_loc_multi_data.in");
			strcpy(map_cnt_data, "map_cnt_multi_data.in");
			strcpy(shortest_way, "./shortest_way2.out");
		}
		
		else if(!strcmp(argv[3], "multi3")){
			strcpy(map_loc_data, "map_loc_multi_data.in");
			strcpy(map_cnt_data, "map_cnt_multi_data.in");
			strcpy(shortest_way, "./shortest_way3.out");
		}

		else{

			printf(" Error : select mod multi1 or multi2 \n");
			exit(1);

		}

	}


	FILE *fin_loc = fopen(map_loc_data, "r");
	FILE *fin_cnt = fopen(map_cnt_data, "r");
	FILE *fin_shortest_way = fopen(shortest_way, "w");

	GRAPH* graph = create_graph_gps();

	while(1){
	
		fscanf(fin_loc, "%d", &id);
		fscanf(fin_loc, "%f", &data_x); 
		fscanf(fin_loc, "%f", &data_y); 

		/* for feof properties */
		if(feof(fin_loc))
			break;

		if(!g_insert_vertex_gps(graph, id, data_x, data_y)){
			#ifdef DEBUG
			printf("graph vertex insersion failed: %d\n", id);
			#endif
		}
	}

	#ifdef DEBUG
	print_vertex_all(graph);
	printf("\n");
	#endif

	//arc insertion test

	int loc_a, loc_b;
	int traffic;

	srand(1);


	#define SIZE 14	
	/* DATA Connnection */


	FILE *read_fp;
	char buffer[SIZE];
	char tmp[SIZE];
	int chars_read;

	memset(buffer, '\0', sizeof(buffer));
	read_fp = popen("./map_cnt_multi_data", "r");
	if(read_fp != NULL){
		chars_read = fread(buffer, sizeof(char), SIZE, read_fp);
		while(chars_read > 0){
			buffer[chars_read - 1] = '\0';
			buffer[4] = '\0';
			buffer[9] = '\0';
			
			strcpy(tmp, buffer);
			loc_a = atoi(tmp);
			
			strcpy(tmp, &buffer[5]);
			loc_b = atoi(tmp);

			strcpy(tmp, &buffer[10]);
			traffic = atoi(tmp);

			if(!insert_arc(graph, loc_a, loc_b, traffic)){
					
				#ifdef DEBUG
				printf("graph arc insertion failed[already exists]: %d -> %d\n", loc_a, loc_b);
				#endif
			}
			chars_read = fread(buffer, sizeof(char), SIZE, read_fp);
	
		}

		pclose(read_fp);
	}
	


	#ifdef NONO
	while(1){	

		fscanf(fin_cnt, "%d %d %d", &loc_a, &loc_b, &traffic);

		if(feof(fin_cnt))
			break;

		if(!insert_arc(graph, loc_a, loc_b, traffic)){

			printf("graph arc insertion failed: %d -> %d\n", loc_a, loc_b);
		}

		else
			printf("graph arc insertion ok: %d -> %d\n", loc_a, loc_b);
	}

	#endif

	/* GRAPH CONNECTION */
	#ifdef DEBUG
	printf("\nGraph's Arc:\n");
	print_arc_all(graph);
	printf("\n");
	#endif

	/* GRAPH BFS TRAVERSE */
	#ifdef DEBUG
	printf(" PRINT GRAPH : BFS \n");
	g_bfs_gps(graph, 5);
	printf("\n");
	#endif
	
	/* GRAPH DFS TRAVERSE */
	#ifdef DEBUG
	printf(" PRINT GRAPH : DFS \n");
	g_dfs_gps(graph, 5);
	printf("\n");
	#endif


	/* FIND SHORTEST WAY BY DIJKSTRA FROM target */


//	g_generate_crosspoint(fin_loc);

	if(argc < 3){
		//g_generate_line(fin_loc, fin_cnt);
		printf(" Type Start point to End point\n");
		printf(" For example, ./path 9 51 (HTML created) \n");
		printf(" If you want multiple vertex points, Add 'multi' \n");
		printf(" For example, ./path 1 3995 multi (HTML not created) \n");
		
	}
	else if(argc == 3)
		g_generate_shortest_path(graph, atoi(argv[1]), atoi(argv[2]), argv);
	
	else if(argc == 4)
		g_generate_shortest_path(graph, atoi(argv[1]), atoi(argv[2]), argv);


	else if(argc > 4)
		printf(" Type correct Starting point & End point");

	fclose(fin_loc);
	fclose(fin_cnt);
	fclose(fin_shortest_way);
	
	return 0;
}
