#include <stdio.h>
#include "ADT_heap.h"


int compare(void *x, void *y){
	
	
	if(*(int *)x > *(int *)y)
		return 1;
	else if(*(int *)x < *(int *)y)
		return -1;
	else	
		return 0;
}


int main(){

	HEAP* heap = heapCreate(50, compare); 

	int i;	
	void *temp;
	int data[20] = {2,1,45,6,7,8,3,4,34,31,63,22,54,23,25,24,46,234,65,39};
	
	for(i = 0; i < 20; i++){
		heapInsert(heap, &data[i]);
	}

	
	for(i = 0; i < 20; i++){

		heapDelete(heap, &temp);
		printf(" %d\n", *(int *)temp);

	}



}
