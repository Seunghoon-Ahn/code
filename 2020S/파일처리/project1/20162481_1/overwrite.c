#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int offset;
	int len;
	int fd;

	if((fd = open(argv[1], O_RDWR | O_EXCL, 0644)) < 0) {
			printf("File Open Error!\n");
			return 0;
	}

	offset = atoi(argv[2]);
	len = strlen(argv[3]);

	if(lseek(fd, (off_t)offset, SEEK_SET) < 0) {
		printf("lseek error\n");
		return 0;
	}

	write(fd, argv[3], len);

	return 0;
}

