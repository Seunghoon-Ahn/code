#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int offset;
	int fd;
	char* buf;
	int len;
	int count;

	if((fd = open(argv[1],O_RDWR | O_EXCL, 0640)) < 0 ) {
		printf("File open error!\n");
		return 0;
	}
	if((len = lseek(fd, 0, SEEK_END)) < 0) {
		printf("lseek error\n");
		return 0;
	}

	if(lseek(fd, 0, SEEK_SET) < 0) {
		printf("lseek error2\n");
		return 0;
	}
	buf = malloc(sizeof(char) * (len+1));
	offset = atoi(argv[2]);
	read(fd, buf, len);

	lseek(fd, offset, SEEK_SET);
	write(fd, argv[3], strlen(argv[3]));
	count = lseek(fd, 0, SEEK_CUR);
	write(fd, &buf[count - strlen(argv[3])], len - offset);
	//ftruncate(fd, len + strlen(argv[3]));


	return 0;
}

