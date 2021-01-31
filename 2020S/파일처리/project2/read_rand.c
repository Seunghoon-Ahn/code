#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

#define SUFFLE_NUM 100000

void GenRecordSequence(int *list, int n);
void swap(int *a, int *b);

int main(int argc, char *argv[]) {
	int *read_order_list;
	int num_of_records, i;
	struct timeval t_start, t_end, t_dif;
	char buf[102];
	FILE *fp = NULL;

	fp = fopen(argv[1], "r");
	fseek(fp, 0, SEEK_END);

	num_of_records = ftell(fp) / 100;

	read_order_list = (int *)malloc(sizeof(int) * num_of_records);

	GenRecordSequence(read_order_list, num_of_records);
	
	gettimeofday(&t_start, NULL);
	for(i = 0; i < num_of_records; i++) {
		fseek(fp, 100 * read_order_list[i], SEEK_SET);
		fread(buf, 100, 1, fp);
	}
	gettimeofday(&t_end, NULL);
	free(read_order_list);
	fclose(fp);
	
	t_dif.tv_usec = (t_end.tv_sec - t_start.tv_sec) * 1000000 + t_end.tv_usec - t_start.tv_usec;

	printf("#records: %d timecost: %ld us\n", num_of_records, t_dif.tv_usec);
	return 0;
}

void GenRecordSequence(int *list, int n){
	int i, j, k;

	srand((unsigned int)time(0));

	for(i=0; i<n; i++) {
		list[i] = i;
	}

	for(i=0; i<SUFFLE_NUM; i++) {
		j = rand() % n;
		k = rand() % n;
		swap(&list[j], &list[k]);
	}
	return;
}

void swap(int *a, int *b) {
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;

	return;
}

