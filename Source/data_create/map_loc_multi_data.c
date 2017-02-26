#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 3333

//#define NEXT

int main(){

	int i;
	int value;


	#ifndef NEXT
	FILE *fout = fopen("map_loc_multi_data.in", "w");
	#endif

	#ifdef NEXT
	FILE *fout = fopen("map_loc_multi_data2.in", "w");
	#endif

	int value_array_state1[DATA_SIZE] = {0, };
	int value_array1[DATA_SIZE] = {0, };

	int value_array_state2[DATA_SIZE] = {0, };
	int value_array2[DATA_SIZE] = {0, };

	int value_array_state3[DATA_SIZE] = {0, };
	int value_array3[DATA_SIZE] = {0, };

	float lng[DATA_SIZE] = {0, };
	float lat[DATA_SIZE] = {0, };

	srand(3);
	for(i = 0; i < DATA_SIZE; ){

		value = (rand()%DATA_SIZE);
	
		if(value_array_state1[value] == 0){

			#ifdef NEXT
			value_array1[i] = value + DATA_SIZE + 1;
			#endif

			#ifndef NEXT
			value_array1[i] = value+1;
			#endif

			value_array_state1[value] = 1;
			i++;
		}		
	}

	srand(50);
	for(i = 0; i < DATA_SIZE; ){

		value = (rand()%DATA_SIZE);
	
		if(value_array_state2[value] == 0){

			value_array2[i] = value+1;
			value_array_state2[value] = 1;
			i++;
		}		
	}

	srand(13);
	for(i = 0; i < DATA_SIZE; ){

		value = (rand()%DATA_SIZE);
	
		if(value_array_state3[value] == 0){

			value_array3[i] = value+1;
			value_array_state3[value] = 1;
			i++;
		}		
	}

	for(i = 0 ; i < DATA_SIZE; i++){

		lat[i] = (float)(value_array2[i] * 18) / 1000000 + 35.885;
		lng[i] = (float)(value_array3[i] * 18) / 1000000 + 128.605;

	}

	for(i = 0 ; i < DATA_SIZE; i++){
		fprintf(fout, "%3d  %f  %f\n", value_array1[i], lat[i], lng[i]);
	}
	
	fclose(fout);

}
