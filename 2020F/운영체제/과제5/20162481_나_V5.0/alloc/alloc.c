#include "alloc.h"

typedef struct _memory{
	int check;
	int pnum;
}mymemory;

mymemory marr[PAGESIZE / MINALLOC];
char *location = 0; //save the start address of 4KB page
int flags = PROT_WRITE | PROT_READ | PROT_EXEC; //flags for mmap
int ptr = 1; //index number for each memory user
int flen = PAGESIZE	/ MINALLOC; //max number of block of each page

int init_alloc(void) {
	char *tmp = mmap(NULL, PAGESIZE, flags, MAP_SHARED | MAP_ANON, -1, 0);
	if(tmp < 0)
		return 1;
	else {
		location = tmp;
		memset(marr, 0, sizeof(marr));
		return 0;
	}
}

int cleanup(void) {
	int tmp = munmap(location, PAGESIZE);
	if(tmp == -1)
		return 1;
	else
		return 0;
}

char *alloc(int size) {
	int block = size / MINALLOC;
	int ok = 0;
	int i;
	if(size % MINALLOC)
		return NULL;
	for(i = 0; i <= flen - block; i++) {
		int count = 0;
		for(int j = i; j < i + block; j++) {
			if(marr[j].check == 1)
				count++;
		}
		if(count == 0) {
			for(int tmp = i; tmp < i + block; tmp++) {
				marr[tmp].check = 1;
				marr[tmp].pnum = ptr;
			}
			ok = 1;
			ptr++;
			break;
		}
	}
	if(ok == 0)
		return NULL;
	else
		return (location + i * MINALLOC);
}

void dealloc(char * start) {
	int loc = (start - location) / MINALLOC;
	int del_check, del_pnum;

	del_check = marr[loc].check;
	del_pnum = marr[loc].pnum;

	for(int i = loc; i < flen; i++) {
		if(marr[i].check == del_check && marr[i].pnum == del_pnum) {
			marr[i].check = 0;
			marr[i].pnum = 0;
		}
		else
			break;
	}
	return;
}