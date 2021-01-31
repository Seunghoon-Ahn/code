#include "alloc.h"
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>

struct memory{
	char *addr; 
	int size;
	bool alloc;
};

struct memory m[10000];
int fd;
char *addr;

int init_alloc()
{
	int i = 1;
	int fd;
	//char *addr;

	if((fd = open("ab", O_CREAT | O_RDWR, 0644)) < 0)
	{
		printf("open error\n");
		return errno;
	}

	addr = mmap(0, PAGESIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

	if(addr == MAP_FAILED)
	{
		printf("mmap error\n");
		return errno;
	}

	for(int i = 0; i < PAGESIZE; i++)
		write(fd, "0", 1);

	//set struct size MINALLOC 
	m[i].size = PAGESIZE;
	m[i].addr = addr;
	i++;

	for(; i <= PAGESIZE/MINALLOC; i++)
	{
		m[i].alloc = false;
		//m[i].addr = addr;
		m[i].addr += MINALLOC;
		m[i].addr = addr;
	}
	m[i].size = PAGESIZE;

	return 0;
}

int cleanup()
{
	int ret;
 
     //ret = munmap(m[0].addr, PAGESIZE);
     ret = munmap(addr, PAGESIZE);
 
     for(int i = 0; i <= 1000; i++)
     {
         m[i].addr ='\0';
         m[i].size = 0;
     }
 
     if(!ret)
         return ret;
     else
         return errno;
}

char *alloc(int len)
{
	if(len % MINALLOC != 0 || len > PAGESIZE) 
		return NULL;

	int i = 0; // memory index
    int end_m; // end of allocated memroy

	for(i = 1; i <= PAGESIZE/MINALLOC; )
	{
		if(m[i].size >= len && m[i].alloc == false)
			break;

		i += m[i].size / MINALLOC;
	}


	if(i == PAGESIZE/MINALLOC + 1 || i == 0)
		return NULL;

	end_m = i + len/MINALLOC - 1; // find end of allocated memory index
 
    if(end_m > PAGESIZE / MINALLOC)
        return NULL;

    if(m[i].size > len)
    {
        m[end_m + 1].size = m[i].size - len;
        m[end_m + 1].addr = m[i].addr + len;
    }

    m[i].size = len;
    m[i].alloc = true;
    m[end_m].size = len;
    m[end_m].alloc = true;


    return m[i].addr;
}

void dealloc(char *free)
{
	int i = 0;
	//int j = 0;
	//bool check = false;

	for(i = 1; i <= PAGESIZE/MINALLOC; )
	{
		if(m[i].addr == free)
			break;

		i += m[i].size / MINALLOC;
	}

	m[i].alloc = false;
	
	int idx_end_m = i + m[i].size/MINALLOC - 1; // end of allocated memory
	m[idx_end_m].alloc = false;

	if(!m[idx_end_m + 1].alloc)//next block is free
	{
		int idx_next_end_m = idx_end_m + m[idx_end_m].size/MINALLOC;
		m[i].size += m[idx_end_m + 1].size;

		m[idx_next_end_m].size += m[idx_end_m].size;
		m[idx_end_m].size = MINALLOC;

		m[idx_end_m].alloc = false;
		idx_end_m = idx_next_end_m;
	}

	if(i != 1 && (!m[i - 1].alloc)) // previous block is free
	{
		int idx_before_first_m = i - m[i-1].size/MINALLOC;

		m[idx_before_first_m].size += m[i].size;
		m[idx_end_m].size = m[idx_before_first_m].size;
	}

}
