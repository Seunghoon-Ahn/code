#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int offset;
	int rbyte;
	int fd;
	int length;
	char *buf;

	if((fd = open(argv[1], O_RDONLY)) < 0) {
		printf("File open Error!\n");
		return 0;
	}

	offset = atoi(argv[2]);
	rbyte = atoi(argv[3]);

	if((lseek(fd, (off_t)offset, SEEK_SET)) < 0) {
		printf("Offset move error!\n");
		return 0;
	}

	buf = malloc(sizeof(char) * (rbyte+1));
	length = read(fd, buf, rbyte);

	write(1, buf, length);
	
	free(buf);
	
	return 0;
}

