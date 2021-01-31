#include "rwlock.h"

long *max_element(long* start, long* end){
	int i;
	long *max=start;

//	printf("in max_element\n");
//	printf("%ld",start[0]);
	for(i=1;(start+i)<end;i++){
		if(*max < start[i])
			max = start+i;
//		printf(", %ld",start[i]);
	}
//	printf("\n");

//	printf("max : %ld\n",max[0]);

	return max;
}

long *min_element(long* start, long* end){
	int i;
	long *min = start;

	for(i=1;(start+i)<end;i++){
		if(*min > start[i])
			min = start+i;
	}

	return min;
}
