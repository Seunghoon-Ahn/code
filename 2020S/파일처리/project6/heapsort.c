#include <stdio.h>
#include "person.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void make_sort(char **heaparray, int num); //힙 + 갯수
int total_record;

//필요한 경우 헤더 파일과 함수를 추가할 수 있음

// 과제 설명서대로 구현하는 방식은 각자 다를 수 있지만 약간의 제약을 둡니다.
// 레코드 파일이 페이지 단위로 저장 관리되기 때문에 사용자 프로그램에서 레코드 파일로부터 데이터를 읽고 쓸 때도
// 페이지 단위를 사용합니다. 따라서 아래의 두 함수가 필요합니다.
// 1. readPage(): 주어진 페이지 번호의 페이지 데이터를 프로그램 상으로 읽어와서 pagebuf에 저장한다
// 2. writePage(): 프로그램 상의 pagebuf의 데이터를 주어진 페이지 번호에 저장한다
// 레코드 파일에서 기존의 레코드를 읽거나 새로운 레코드를 쓸 때나
// 모든 I/O는 위의 두 함수를 먼저 호출해야 합니다. 즉, 페이지 단위로 읽거나 써야 합니다.

//
// 페이지 번호에 해당하는 페이지를 주어진 페이지 버퍼에 읽어서 저장한다. 페이지 버퍼는 반드시 페이지 크기와 일치해야 한다.
//
void readPage(FILE *fp, char *pagebuf, int pagenum)
{
	fseek(fp, PAGE_SIZE * pagenum, SEEK_SET);
	fread((void *)pagebuf, PAGE_SIZE, 1, fp);

	return;
}

//
// 페이지 버퍼의 데이터를 주어진 페이지 번호에 해당하는 위치에 저장한다. 페이지 버퍼는 반드시 페이지 크기와 일치해야 한다.
//
void writePage(FILE *fp, const char *pagebuf, int pagenum)
{
	fseek(fp, PAGE_SIZE * pagenum, SEEK_SET);
	fwrite((void *)pagebuf, PAGE_SIZE, 1, fp);

	return;
}

void make_sort(char **heaparray, int num) {
	int i = num;
	long long parent, son;
	char tmpbuf[RECORD_SIZE];
	memset(tmpbuf, 0, RECORD_SIZE);
	int checksum = 0;
	if(i == 1)
		return;

	while(1) {
		if(!(i / 2))
			break;
		son = atoll(heaparray[i]);
		parent = atoll(heaparray[i/2]);
		if(son < parent) {
			strcpy(tmpbuf, heaparray[i]);
			strcpy(heaparray[i], heaparray[i/2]);
			strcpy(heaparray[i/2], tmpbuf);
			i = i / 2;
		}
		else
			break;
	}
	return;
}


//
// 주어진 레코드 파일에서 레코드를 읽어 heap을 만들어 나간다. Heap은 배열을 이용하여 저장되며, 
// heap의 생성은 Chap9에서 제시한 알고리즘을 따른다. 레코드를 읽을 때 페이지 단위를 사용한다는 것에 주의해야 한다.
//
void buildHeap(FILE *inputfp, char **heaparray)
{
	int recordcnt, pagecnt;
	int tmpcnt = 0;
	char recordbuf[RECORD_SIZE];
	char pagebuf[PAGE_SIZE];
	char header[PAGE_SIZE];

	memset(recordbuf, 0, RECORD_SIZE);
	memset(pagebuf, 0, PAGE_SIZE);
	memset(header, 0, PAGE_SIZE);

	readPage(inputfp, header, 0);

	memcpy(&pagecnt, header, 4);
	memcpy(&recordcnt, header + 4, 4);

	total_record = recordcnt;

	for(int i = 1; i < pagecnt; i++) {
		memset(pagebuf, 0, sizeof(pagebuf));
		readPage(inputfp, pagebuf, i); //페이지 하나 읽어옴
		for(int j = 0; j < (PAGE_SIZE / RECORD_SIZE); j++) {
			if(tmpcnt == recordcnt)
				break;
			tmpcnt++;
			memset(recordbuf, 0, RECORD_SIZE);
			strncpy(recordbuf, pagebuf + j * RECORD_SIZE, RECORD_SIZE);
			heaparray[tmpcnt] = (char *)malloc(RECORD_SIZE);
			strcpy(heaparray[tmpcnt], recordbuf);

			make_sort(heaparray, tmpcnt);
		}
	}

	return;
}

//
// 완성한 heap을 이용하여 주민번호를 기준으로 오름차순으로 레코드를 정렬하여 새로운 레코드 파일에 저장한다.
// Heap을 이용한 정렬은 Chap9에서 제시한 알고리즘을 이용한다.
// 레코드를 순서대로 저장할 때도 페이지 단위를 사용한다.
//
void makeSortedFile(FILE *outputfp, char **heaparray)
{ //total_record 가 전체 레코드 갯수
	char pagebuf[PAGE_SIZE];
	char recordbuf[RECORD_SIZE];
	int cnt = total_record, checkpage = 0;
	int pagenum = 1;
	int fullpage = PAGE_SIZE / RECORD_SIZE;

	memset(pagebuf, (char)0xFF, PAGE_SIZE);
	memset(recordbuf, 0, RECORD_SIZE);

	while(cnt) {
		if(checkpage < fullpage) {
			strncpy(pagebuf + checkpage * RECORD_SIZE, heaparray[1], RECORD_SIZE);
			checkpage++;
		}
		else {
			checkpage = 0;
			writePage(outputfp, pagebuf, pagenum);
			pagenum++;
			memset(pagebuf, (char)0xFF, PAGE_SIZE);
			strncpy(pagebuf + checkpage * RECORD_SIZE, heaparray[1], RECORD_SIZE);
			checkpage++;		
		}
		
		strncpy(heaparray[1], heaparray[cnt], RECORD_SIZE);
		cnt--;
		
		if(cnt == 0) {
			if(checkpage != 0)
				writePage(outputfp, pagebuf, pagenum);
			break;
		}

		int i= 1;
		while(1) {
			if(2 * i > cnt && 2 * i + 1 > cnt) //더이상 자식이 없으면 펑
				break;
			
			if(2 * i + 1 > cnt && 2 * i <= cnt) { //왼쪽 자식만 있을때
				long long son = atoll(heaparray[i * 2]);
				long long parent = atoll(heaparray[i]);
				if(son < parent) {
					memset(recordbuf, (char)0xFF, RECORD_SIZE);
					strncpy(recordbuf, heaparray[i], RECORD_SIZE);
					strncpy(heaparray[i], heaparray[i*2], RECORD_SIZE);
					strncpy(heaparray[i * 2], recordbuf, RECORD_SIZE);
					i = i * 2;
				}
				else
					break;
			}
			else {
				long long son1 = atoll(heaparray[i * 2]);
				long long son2 = atoll(heaparray[i * 2 + 1]);
				long long parent = atoll(heaparray[i]);

				if(son1 > son2) {
					memset(recordbuf, (char)0xFF, RECORD_SIZE);
					strncpy(recordbuf, heaparray[i], RECORD_SIZE);
					strncpy(heaparray[i], heaparray[i * 2 + 1], RECORD_SIZE);
					strncpy(heaparray[i * 2 + 1], recordbuf, RECORD_SIZE);
					i = i * 2 + 1;
				}
				else {
					memset(recordbuf, (char)0xFF, RECORD_SIZE);
					strncpy(recordbuf, heaparray[i], RECORD_SIZE);
					strncpy(heaparray[i], heaparray[i * 2], RECORD_SIZE);
					strncpy(heaparray[i * 2], recordbuf, RECORD_SIZE);
					i = i * 2;					
				}
			}
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *inputfp;	// 입력 레코드 파일의 파일 포인터
	FILE *outputfp;	// 정렬된 레코드 파일의 파일 포인터
	char *heaparray[1024];
	char header[PAGE_SIZE];

	setbuf(stdout, NULL);

	memset(heaparray, 0, sizeof(heaparray));
	memset(header, 0, PAGE_SIZE);

	if(argc != 4) {
		fprintf(stderr, "Usage : %s s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	if(argv[1][0] != 's') {
		fprintf(stderr, "Usage : %s s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	if((inputfp = fopen(argv[2], "r+")) == NULL) {
		fprintf(stderr, "%s file open error\n", argv[2]);
		exit(1);
	}
	if((outputfp = fopen(argv[3], "w+")) == NULL) {
		fprintf(stderr, "%s file open error\n", argv[3]);
		exit(1);
	}

	readPage(inputfp, header, 0);
	writePage(outputfp, header, 0);


	buildHeap(inputfp, heaparray);

	makeSortedFile(outputfp, heaparray);

	for(int i = 0; i < 1024; i++)
		free(heaparray[i]);

	fclose(inputfp);
	fclose(outputfp);

	return 0;
}