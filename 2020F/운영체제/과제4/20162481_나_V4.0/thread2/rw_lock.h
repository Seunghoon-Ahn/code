#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct rw_lock
{
	int status;
	int Rnum, Wnum;
	pthread_mutex_t read_mutex;
	pthread_mutex_t write_mutex;
	pthread_cond_t read_cond;
	pthread_cond_t write_cond;
};

void init_rwlock(struct rw_lock * rw);
void r_lock(struct rw_lock * rw);
void r_unlock(struct rw_lock * rw);
void w_lock(struct rw_lock * rw);
void w_unlock(struct rw_lock * rw);
long *max_element(long* start, long* end);
long *min_element(long* start, long* end);
