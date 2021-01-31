// 주의사항
// 1. sectormap.h에 정의되어 있는 상수 변수를 우선적으로 사용해야 함
// 2. sectormap.h에 정의되어 있지 않을 경우 본인이 이 파일에서 만들어서 사용하면 됨
// 3. 필요한 data structure가 필요하면 이 파일에서 정의해서 쓰기 바람(sectormap.h에 추가하면 안됨)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "sectormap.h"

int dd_read(int ppn, char *pagebuf);
int dd_write(int ppn, char *pagebuf);
int dd_erase(int pbn);
int g_collect(void);

int ftl_table[DATAPAGES_PER_DEVICE];
int free_block_number;
int free_page[PAGES_PER_BLOCK * BLOCKS_PER_DEVICE]; //free ppn 저장
int garbage_page[PAGES_PER_BLOCK * BLOCKS_PER_DEVICE]; //가비지 ppn 저장
int check_page[PAGES_PER_BLOCK * BLOCKS_PER_DEVICE] = {0, }; // 가비지 콜렉팅 할때 사용

int free_page_indicator = PAGES_PER_BLOCK * BLOCKS_PER_DEVICE - 1;
int garbage_page_indicator = -1;


void ftl_open()
{
	int i;
	for(i = 0; i < DATAPAGES_PER_DEVICE; i++)
		ftl_table[i] = -1; //초기화

	for(i = PAGES_PER_BLOCK * BLOCKS_PER_DEVICE - 1; i >= 0 ; i--)
		free_page[i] = PAGES_PER_BLOCK * BLOCKS_PER_DEVICE - i - 1;

	free_block_number = DATABLKS_PER_DEVICE; //초기에는 마지막 블록을 free 블록으로 설정

	return;
}

//
// 이 함수를 호출하기 전에 이미 sectorbuf가 가리키는 곳에 512B의 메모리가 할당되어 있어야 한다.
// 즉, 이 함수에서 메모리를 할당받으면 안된다.
//
void ftl_read(int lsn, char *sectorbuf)
{
	int i;
	char pagebuf[PAGE_SIZE];
	memset (pagebuf, 0, sizeof(pagebuf));
	if(ftl_table[lsn] == -1) {
		printf("No Data in this page!!!!\n");
		return;
	}
	else
		dd_read(ftl_table[lsn], pagebuf);
	
	for(i = 0; i < SECTOR_SIZE; i++) {
		if(pagebuf[i] != (char)0xFF)
			sectorbuf[i] = pagebuf[i];
		else
			break;
	}

	return;
}


void ftl_write(int lsn, char *sectorbuf)
{
	char pagebuf[PAGE_SIZE];
	char tmpbuf[PAGE_SIZE];
	int ret;
	int oldppn;
	memset(pagebuf, (char)0xFF, PAGE_SIZE);
	memset(tmpbuf, (char)0xFF, PAGE_SIZE);
	SpareData S;
	S.lpn = lsn;
	S.is_invalid = 0;
	memcpy(pagebuf, sectorbuf, strlen(sectorbuf));
	memcpy(pagebuf + SECTOR_SIZE, &S, sizeof(SpareData));
	 //pagebuf에 데이터 만듦

	if(free_page[free_page_indicator] != free_block_number * PAGES_PER_BLOCK) {
		oldppn = ftl_table[lsn];
		ftl_table[lsn] = free_page[free_page_indicator];
		dd_write(ftl_table[lsn], pagebuf);
		free_page[free_page_indicator] = 0;
		free_page_indicator--;
		check_page[oldppn] = 1;
		garbage_page[garbage_page_indicator + 1] = oldppn;
		garbage_page_indicator++;
	}
	else {
		ret = g_collect();

		if(ret < 0) {
			oldppn = ftl_table[lsn];
			int oldpbn = oldppn / PAGES_PER_BLOCK;
			for(int i = 0; i < DATAPAGES_PER_DEVICE; i++) {
				if(ftl_table[i] / PAGES_PER_BLOCK == oldpbn && ftl_table[i] != oldppn) {
					int temp = ftl_table[i];
					dd_read(ftl_table[i], tmpbuf);
					ftl_table[i] = free_page[free_page_indicator];
					free_page_indicator--;
					dd_write(ftl_table[i], tmpbuf);
				}
				else if (ftl_table[i] / PAGES_PER_BLOCK == oldpbn && ftl_table[i] == oldppn) {
					ftl_table[i] = free_page[free_page_indicator];
					free_page_indicator--;
					dd_write(ftl_table[i], pagebuf);
				}
			}
			dd_erase(oldpbn);
			free_block_number = oldpbn;
			for(int i = 0; i < PAGES_PER_BLOCK; i++) {
				free_page[i] = free_block_number * PAGES_PER_BLOCK + 3 - i;
			}
			free_page_indicator += PAGES_PER_BLOCK;
		}
		else {
			oldppn = ftl_table[lsn];
			ftl_table[lsn] = free_page[free_page_indicator];
			free_page[free_page_indicator] = 0;
			free_page_indicator--;
			check_page[oldppn] = 1;
			garbage_page[garbage_page_indicator + 1] = oldppn;
			garbage_page_indicator++;
			dd_write(ftl_table[lsn], pagebuf);
		}
	}
	return;
}

int g_collect(void) {
	//check가 1이면 가비지인 칸
	//블록하나의 4개의 페이지가 모두 1이면 그 블록을 프리블록으로 지정하고
	//기존의 프리블럭을 사용함

	int i, tmp = 0, j, s;
	int ind = PAGES_PER_BLOCK;
	for(i = 0; i < BLOCKS_PER_DEVICE; i++) {
		tmp = 0;
		if(i != free_block_number) {
			for( j = 0; j < PAGES_PER_BLOCK; j++)
				tmp += check_page[i * PAGES_PER_BLOCK + j];
			if(tmp == PAGES_PER_BLOCK) {
				for( j = 0; j < PAGES_PER_BLOCK; j++)
					check_page[i * PAGES_PER_BLOCK + j] = 0;

				free_block_number = i;

				for( s = 0; s < PAGES_PER_BLOCK; s++) {
					free_page[s + PAGES_PER_BLOCK] = free_page[s];
					free_page[s] = free_block_number * PAGES_PER_BLOCK + PAGES_PER_BLOCK - 1 - s;
				}

				free_page_indicator += PAGES_PER_BLOCK;
				garbage_page_indicator -= PAGES_PER_BLOCK;
				dd_erase(free_block_number);
				return 1;
			}	 
		}
	}
	return -1;
}

void ftl_print() //table, free block number 출력
{
	int i;
	printf("lpn ppn\n");
	for(i = 0; i < DATAPAGES_PER_DEVICE; i++)
		printf("%d %d\n", i, ftl_table[i]);
	printf("free block's pbn=%d\n", free_block_number);
	return;
}
