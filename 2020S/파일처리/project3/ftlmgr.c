#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "flash.h"

FILE *flashfp;	// fdevicedriver.c에서 사용

int dd_read(int ppn, char *pagebuf);
int dd_write(int ppn, char *pagebuf);
int dd_erase(int pbn);
int find_empty_block(void);


int main(int argc, char *argv[])
{	
	char sectorbuf[SECTOR_SIZE]; //512
	char sparebuf[SPARE_SIZE]; //16
	char pagebuf[PAGE_SIZE]; //512+16
	char *blockbuf;
	char mod;
	char fname[1024];
	int res;
	mod = argv[1][0]; // c 파일생성 w 쓰기 r 읽기 e 지우기
	strcpy(fname, argv[2]);

	if(mod == 'c') {

		int blocks = atoi(argv[3]);

		if((flashfp = fopen(fname, "w+")) < 0) {
			fprintf(stderr, "fopen error : %s\n", fname);
			exit(1);
		}

		for(int i = 0; i < blocks; i++)
			res = dd_erase(i);

		if(res == -1)
			fprintf(stderr, "file initialization error\n");
	}
	else if (mod == 'w') {
		char tmpbuf[PAGE_SIZE+1];
		if((flashfp = fopen(fname, "r+")) < 0) {
			fprintf(stderr, "fopen error : %s\n", fname);
			exit(1);
		}

		int ppn = atoi(argv[3]); //페이지 번호
		strcpy(sectorbuf, argv[4]); //섹터에 쓸 데이터
		strcpy(sparebuf, argv[5]); //스페어에 쓸 데이터
		
		memset((void *)pagebuf, (char)0xFF, PAGE_SIZE);
		
		for(int i = 0; i < strlen(sectorbuf); i++)
			pagebuf[i] = sectorbuf[i];
		
		for(int i = 0; i < strlen(sparebuf); i++)
			pagebuf[SECTOR_SIZE + i] = sparebuf[i];

		int emptyblock = find_empty_block(); 

		int pbn = ppn / 4; //내가 써야하는 페이지가 속한 블록 번호
		for(int i = 0; i < PAGE_NUM; i++) {
			memset(tmpbuf, (char)0xFF, PAGE_SIZE);
			tmpbuf[PAGE_SIZE] = '\0';
			if(i != ppn % 4) {
				res = dd_read(pbn * 4 + i, tmpbuf);
				res = dd_write(emptyblock * 4 + i, tmpbuf);
			}
		}
		res = dd_erase(pbn); //블록 소거
		res = dd_write(ppn, pagebuf); //내가 쓰고자 했던거 씀

		for(int i = 0; i <PAGE_NUM; i++) {
			memset(tmpbuf, (char)0xFF, PAGE_SIZE);
			tmpbuf[PAGE_SIZE] = '\0';
			if(i != ppn % 4) {
				res = dd_read(emptyblock * 4 + i, tmpbuf);
				res = dd_write(pbn * 4 + i, tmpbuf);
			}
		}
		if(emptyblock != pbn)
			res = dd_erase(emptyblock);
	}
	else if (mod == 'r') {
		char tmp;
		int i;
		if((flashfp = fopen(fname, "r")) < 0) {
			fprintf(stderr, "fopen error : %s\n", fname);
			exit(1);
		}
		int ppn = atoi(argv[3]);
		res = dd_read(ppn, pagebuf);

		if(res == -1) {
			fprintf(stderr, "read error\n");
			exit(1);
		}

		for(i = 0; i < strlen(pagebuf); i++){
			if(pagebuf[i] == (char)0xFF)
				break;
			else
				printf("%c", pagebuf[i]);
		}
		if((pagebuf[0] != (char)0xFF) && (pagebuf[SECTOR_SIZE] != (char)0xFF))
			printf(" ");
		for(i = SECTOR_SIZE; i < PAGE_SIZE; i++) {
			if(pagebuf[i] == (char)0xFF)
				break;
			else
				printf("%c", pagebuf[i]);
		}
	}
	else if (mod == 'e') {

		if((flashfp = fopen(fname, "r+")) < 0) {
			fprintf(stderr, "fopen error : %s\n", fname);
			exit(1);
		}

		int pbn = atoi(argv[3]); //블록번호 0~99
		res = dd_erase(pbn);
		
		if(res == -1){
			fprintf(stderr, "erase error\n");
			exit(1);
		}
	}

	return 0;
}

int find_empty_block(void) {
	int i, j, x, tmp = 0;
	int ebn = 0, ret;
	char pagebuf[PAGE_SIZE + 1];
	char cmpbuf[PAGE_SIZE + 1];
	memset(cmpbuf, (char)0xFF, PAGE_SIZE);
	memset(pagebuf, (char)0xFF, PAGE_SIZE);
	pagebuf[PAGE_SIZE] = cmpbuf[PAGE_SIZE] = '\0';
	rewind(flashfp);
	fseek(flashfp, 0, SEEK_END);
	long fsize = ftell(flashfp);
	rewind(flashfp);
	int blockcnt = (int)fsize / BLOCK_SIZE;

	for(i = 0; i < blockcnt; i++) {
		tmp = 0;
		for(j = 0; j <PAGE_NUM; j++) {
			ret = dd_read(4 * i + j, pagebuf);
			ret = strncmp(pagebuf, cmpbuf, PAGE_SIZE);
			if(ret != 0) tmp++;
		}
		if(tmp == 0) {
			ebn = i;
			break;
		}
	}
	return ebn;
}
