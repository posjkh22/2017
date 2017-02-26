#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 14
#define VERTEX_NUM_SIZE 4

int main(){

	FILE *read_fp;
	char buffer[SIZE];
	char tmp[SIZE];
	int data1, data2, data3;
	int chars_read;

	memset(buffer, '\0', sizeof(buffer));
	read_fp = popen("./map_cnt_multi_data", "r");
	if(read_fp != NULL){
		chars_read = fread(buffer, sizeof(char), SIZE, read_fp);
		while(chars_read > 0){
			buffer[chars_read - 1] = '\0';
			printf("Reading : %s\n", buffer);
			buffer[4] = '\0';
			buffer[9] = '\0';
			
			strcpy(tmp, buffer);
			data1 = atoi(tmp);
			
			strcpy(tmp, &buffer[5]);
			data2 = atoi(tmp);

			strcpy(tmp, &buffer[10]);
			data3 = atoi(tmp);

			printf(" %d %d %d \n", data1, data2, data3);
			
			chars_read = fread(buffer, sizeof(char), SIZE, read_fp);
	
		}

		pclose(read_fp);
		exit(EXIT_SUCCESS);
	}
	
	exit(EXIT_FAILURE);

}
