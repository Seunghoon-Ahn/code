#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
	FILE *fp = NULL;
	int i, rnum;
	struct timeval t_start, t_end, t_dif;
	char buf[102];
	char *fname = argv[1];
	fp = fopen(fname, "r");

	if(fp == NULL) {
		printf("File open error!\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	rnum = ftell(fp) / 100;
	fseek(fp, 0, SEEK_SET);

	
	gettimeofday(&t_start, NULL);
	
	for(i = 0; i < rnum; i++)
		fread(buf, 100, 1, fp);
	
	gettimeofday(&t_end, NULL);
	fclose(fp);
	
	t_dif.tv_usec = (t_end.tv_sec - t_start.tv_sec) * 1000000 + t_end.tv_usec - t_start.tv_usec;
	
	printf("#records: %d timecost: %ld us\n", rnum, t_dif.tv_usec);

	return 0;
}
