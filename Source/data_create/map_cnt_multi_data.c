#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 3333

//#define NEXT

int main(){

	int i;
	int value;
	int traffic;
	int plus1, plus2;	

	#ifndef NEXT
	FILE *fout = fopen("map_cnt_multi_data.in", "w");
	#endif

	#ifdef NEXT
	FILE *fout = fopen("map_cnt_multi_data2.in", "w");
	#endif

	int from_id_array[DATA_SIZE] = {0, };
	int from_id_state[DATA_SIZE] = {0, };

	int to_id_array[DATA_SIZE] = {0, };
	int to_id_state[DATA_SIZE] = {0, };

	int to_id_array2[DATA_SIZE] = {0, };
	int to_id_state2[DATA_SIZE] = {0, };

	int to_id_array3[DATA_SIZE] = {0, };
	int to_id_state3[DATA_SIZE] = {0, };

	srand(1);


	for(i = 0; i < DATA_SIZE; ){

		value = (rand()%DATA_SIZE);

		if(from_id_state[value] == 0){

			#ifdef NEXT
			from_id_array[i] = value+ DATA_SIZE + 1;
			#endif

			#ifndef NEXT
			from_id_array[i] = value+1;
			#endif

			from_id_state[value] = 1;
			i++;
			
		}		
	}

	srand(2);


	for(i = 0; i < DATA_SIZE; ){

		value = (rand()%DATA_SIZE);

		if(to_id_state[value] == 0){

			#ifdef NEXT
			to_id_array[i] = value+ DATA_SIZE + 1;
			#endif

			#ifndef NEXT
			to_id_array[i] = value+1;
			#endif

			to_id_state[value] = 1;
			i++;
			
		}		
	}

	srand(3);


	for(i = 0; i < DATA_SIZE; ){

		value = (rand()%DATA_SIZE);

		if(to_id_state2[value] == 0){

			#ifdef NEXT
			to_id_array2[i] = value+ DATA_SIZE + 1;
			#endif

			#ifndef NEXT
			to_id_array2[i] = value+1;
			#endif
			to_id_state2[value] = 1;
			i++;
			
		}		
	}

	srand(9);


	for(i = 0; i < DATA_SIZE; ){

		value = (rand()%DATA_SIZE);

		if(to_id_state3[value] == 0){

			#ifdef NEXT
			to_id_array3[i] = value+ DATA_SIZE + 1;
			#endif

			#ifndef NEXT
			to_id_array3[i] = value+1;
			#endif

			to_id_state3[value] = 1;
			i++;
			
		}		
	}

	srand(11);

	for(i = 0 ; i < DATA_SIZE; i++){

		traffic = rand()%256;
		fprintf(fout, "%3d  %3d  %3d\n", from_id_array[i], to_id_array[i], traffic);

		traffic = rand()%256;
		fprintf(fout, "%3d  %3d  %3d\n", from_id_array[i], to_id_array2[i], traffic);

		traffic = rand()%256;
		fprintf(fout, "%3d  %3d  %3d\n", from_id_array[i], to_id_array3[i], traffic);


		traffic = rand()%256;
		plus1 = rand()%DATA_SIZE +1;
		plus2 = rand()%DATA_SIZE +1;
		fprintf(fout, "%3d  %3d  %3d\n", plus1, plus2, traffic);

		traffic = rand()%256;
		plus1 = rand()%DATA_SIZE +1;
		plus2 = rand()%DATA_SIZE +1;
		fprintf(fout, "%3d  %3d  %3d\n", plus1, plus2, traffic);

		traffic = rand()%256;
		plus1 = rand()%DATA_SIZE +1;
		plus2 = rand()%DATA_SIZE +1;
		fprintf(fout, "%3d  %3d  %3d\n", plus1, plus2, traffic);
	}

	fclose(fout);

}
