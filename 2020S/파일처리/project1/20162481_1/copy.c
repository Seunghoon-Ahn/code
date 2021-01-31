#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char strtmp[101] = { 0 };
	int tmp;
	FILE *start, *end;
	
	if((start = fopen(argv[1], "r")) == NULL) {
		printf("Source File Open Error!\n");
		return 0;
	}
	if((end = fopen(argv[2], "w")) == NULL) {
		printf("Copy File Open Error!\n");
		return 0;
	}

	while(feof(start) == 0) {
		tmp = fread(strtmp , sizeof(char), 100, start);
		fwrite(strtmp, sizeof(char), tmp, end);
		memset(strtmp, 0, 101);
	}
	fclose(start);
	fclose(end);

	return 0;
}

