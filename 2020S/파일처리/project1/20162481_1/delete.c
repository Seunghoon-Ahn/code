#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int offset, dbyte;
	int fd;
	char* buf;
	int len;
	int newlen;

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
	dbyte = atoi(argv[3]);
	read(fd, buf, len);
	lseek(fd, offset, SEEK_SET);
	if(offset + dbyte > len)
		ftruncate(fd, offset);
	else{
		write(fd, &buf[offset + dbyte], len - dbyte - offset);
		ftruncate(fd, len - dbyte);
	}
	close(fd);
	free(buf);
	return 0;
}

