#include "ealloc.h"

typedef struct {
	int check;
	int pnum;
}mymemory; //struct for save usages of each slot of memory

mymemory marr[MAX_PAGE_NUM][PAGESIZE / MINALLOC];
int curpage = -1;
int maxpage = MAX_PAGE_NUM - 1; // 3 - max page number (0, 1, 2, 3)
char *location[MAX_PAGE_NUM]; //start adress for each page
int curpnum = 1; //put index for each memory user
int max_num_block = PAGESIZE / MINALLOC; //max number of blocks per each 4KB page
int flags = PROT_WRITE | PROT_READ | PROT_EXEC; //flags for mmap

void init_alloc(void) {
	int i, j;

	for(i = 0; i < MAX_PAGE_NUM; i++) {
		for(j = 0; j < PAGESIZE / MINALLOC; j++) {
			marr[i][j].check = 0;
			marr[i][j].pnum = 0;
		}
	}

	return;
} 

char *alloc(int size) {
	int block = size / MINALLOC;
	int ok = 0; //index of memopry mapped (0, 1) 
	int i, j;
	if(size % MINALLOC || size > PAGESIZE) //something wrong with size
		return NULL;

	if(curpage == -1) { //페이지가 한개도 매핑되지 않았을때
		curpage++;
		location[curpage] = mmap(NULL, PAGESIZE, flags, MAP_SHARED | MAP_ANON, -1, 0);
		if(location[curpage] < 0)
			return NULL;
		for(int i = 0; i < block; i++) {
			marr[curpage][i].check = 1;
			marr[curpage][i].pnum = curpnum;
		}
		curpnum++;
		return location[curpage];
	}
	else {
		for(i = 0; i <= curpage; i++) { //per page
			for(j = 0; j <= max_num_block - block; j++) { //per blocks in page
				int count = 0;
				for(int k = j; k < j + block; k++) {
					if(marr[i][k].check == 1)
						count++;
				}

				if(count == 0) { //if page has available size of empty slot
					for(int x = j; x < j + block; x++) {
						marr[i][x].check = 1;
						marr[i][x].pnum = curpnum;
					}
					ok = 1;
					curpnum++;
					break;
				}
			}
			if(ok)
				break;
		}
		if(ok == 0) {  //넣을 자리가 없을때
			if(curpage == maxpage) //페이지를 더 만들 수 없는 상태
				return NULL;
			curpage++;
			location[curpage] = mmap(NULL, PAGESIZE, flags, MAP_SHARED | MAP_ANON, -1, 0);
			if(location[curpage] < 0)
				return NULL;
			for(int tmp = 0; tmp < block; tmp++) {
				marr[curpage][tmp].check = 1;
				marr[curpage][tmp].pnum = curpnum;
			}
			curpnum++;
			return location[curpage];			
		}
		else //넣을 자리가 있어서 넣었을때
			return location[i] + j * MINALLOC;
	}
}

void dealloc(char * start) {
	int pageloc, blockloc;
	int del_pnum;
	
	for(pageloc = 0; pageloc <= curpage; pageloc++) {		
		if(location[pageloc] <= start && start < location[pageloc] + max_num_block * MINALLOC)
			break;
	}
	 //find the page number of chunk for delete
	blockloc = (start - location[pageloc]) / MINALLOC;

	del_pnum = marr[pageloc][blockloc].pnum;

	for(int i = blockloc; i < max_num_block; i++) {
		if(marr[pageloc][i].pnum == del_pnum) {
			marr[pageloc][i].check = 0;
			marr[pageloc][i].pnum = 0;
		}
		else
			break;
	}
	return;
}

void cleanup(void) {
	int i, j;

	for(i = 0; i < MAX_PAGE_NUM; i++) {
		for(j = 0; j < PAGESIZE / MINALLOC; j++) {
			marr[i][j].check = 0;
			marr[i][j].pnum = 0;
		}
	}
	return;
}