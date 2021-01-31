#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int fd1;
	int fd2;
	int length;
	char *buf;
	if((fd1 = open(argv[1], O_RDWR | O_EXCL, 0644)) < 0) {
		printf("File 1 Open Error!\n");
		return 0;
	}

	if((fd2 = open(argv[2], O_RDWR | O_EXCL, 0644)) < 0) {
		printf("File open Error!\n");
		return 0;
	}

	if(lseek(fd1, 0, SEEK_END) < 0) {
		printf("lseek error\n");
		return 0;
	}
		
	if((length = lseek(fd2, 0, SEEK_END)) < 0) {
		printf("lseek error2\n");
		return 0;
	}
	
	if(lseek(fd2, 0, SEEK_SET) < 0) {
		printf("lseek error3\n");
		return 0;
	}
		
	buf = malloc(sizeof(char) * (length+1));
	read(fd2, buf, length);
	write(fd1, buf, length);

	return 0;
}
