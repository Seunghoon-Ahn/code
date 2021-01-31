#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

//granularity of memory to mmap from OS
#define PAGESIZE 4096 

//minimum allocation size
#define MINALLOC 256

//maximum number of page
#define MAX_PAGE_NUM 4

// function declarations to support
void init_alloc(void);
char *alloc(int size);
void dealloc(char *start);
void cleanup(void);
