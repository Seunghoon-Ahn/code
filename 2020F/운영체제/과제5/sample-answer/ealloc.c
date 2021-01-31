#include "ealloc.h"
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>

struct memory{
	char *addr; 
	int size;
	bool alloc;
};

struct memory m[10][10000];
int count;// page num
int fd;

void init_alloc()
{
	char *addr;

	if((fd = open("b", O_CREAT | O_RDWR, 0644)) < 0)
	{
		printf("open error\n");
		return;
	}

	//set struct size 256
	for(int i = 1; i <= PAGESIZE/MINALLOC; i++)
	{
		//m[count][i].size = MINALLOC;
		m[count][i].alloc = false;
	}

}

void cleanup()
{
	for(int j = 0; j < count; j++)
	{
		for(int i = 1; i <= PAGESIZE/MINALLOC; i++)
		{
			m[j][i].addr = '\0';
			m[j][i].size = 0;
		}
	}

	close(fd);

}

char *alloc(int len)
{
	if(len % MINALLOC != 0 || len > PAGESIZE) 
		return NULL;

	int i = 0; // memory index
	int j = 0; // page index
	int end_m; // end of allocated memroy
	bool check = false; // check alloc memory

	for(j = 0; j < count; j++)
	{
		for(i = 1; i <= PAGESIZE/MINALLOC; )
		{
			if(m[j][i].size >= len && m[j][i].alloc == false)
			{
				check = true;
				break;
			}

			i += m[j][i].size / MINALLOC;
		}

		if(check)
			break;
	}

	if(i == PAGESIZE/MINALLOC + 1 || i == 0)	
	{
		//alloc new page or return NULL
		//check PAGESIZE * 4

		char *addr;
		struct stat statbuf;

		if(stat("b", &statbuf) < 0)
		{
			printf("stat error\n");
			return NULL;
		}

		if(statbuf.st_size >= PAGESIZE * 4)
			return NULL;

		addr = mmap(NULL, PAGESIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, statbuf.st_size);
		printf("addr %p\n", addr);

		if(addr == MAP_FAILED)
		{
			printf("mmap error\n");
			return NULL;
		}


		for(int i = 0; i < PAGESIZE; i++) 
			write(fd, "0", 1);


		m[count][1].size = PAGESIZE;
		for(int i = 1; i <= PAGESIZE/MINALLOC; i++)//initialize struct
		{
			//m[count][i].size = MINALLOC;
			m[count][i].addr = addr;
			addr += MINALLOC;
			m[count][i].alloc = false;
		}
		m[count][PAGESIZE/MINALLOC].size = PAGESIZE;

		count++;
		i = 1;
	}

	end_m = i + len/MINALLOC - 1; // find end of allocated memory index

	if(end_m > PAGESIZE / MINALLOC)
		return NULL;

	if(m[j][i].size > len)
	{
		m[j][end_m + 1].size = m[j][i].size - len;
		m[j][end_m + 1].addr = m[j][i].addr + len;
	}
	
	m[j][i].size = len;
	m[j][i].alloc = true;
	m[j][end_m].size = len;
	m[j][end_m].alloc = true;


	return m[j][i].addr;

}

void dealloc(char *free)
{
	int i = 0;
	int j = 0;
	bool check = false;

	for(j = 0; j < count; j++)
	{
		for(i = 1; i <= PAGESIZE/MINALLOC; )
		{
			if(m[j][i].addr == free)
			{
				check = true;
				break;
			}

			i += m[j][i].size / MINALLOC;
		}

		if(check)
			break;
	}

	m[j][i].alloc = false;
	
	int idx_end_m = i + m[j][i].size/MINALLOC - 1; // end of allocated memory
	m[j][idx_end_m].alloc = false;

	if(!m[j][idx_end_m + 1].alloc)//next block is free
	{
		int idx_next_end_m = idx_end_m + m[j][idx_end_m].size/MINALLOC;
		m[j][i].size += m[j][idx_end_m + 1].size;

		m[j][idx_next_end_m].size += m[j][idx_end_m].size;
		m[j][idx_end_m].size = MINALLOC;

		m[j][idx_end_m].alloc = false;
		idx_end_m = idx_next_end_m;
	}

	if(i != 1 && (!m[j][i - 1].alloc)) // previous block is free
	{
		int idx_before_first_m = i - m[j][i-1].size/MINALLOC;

		m[j][idx_before_first_m].size += m[j][i].size;
		m[j][idx_end_m].size = m[j][idx_before_first_m].size;
	}

}
