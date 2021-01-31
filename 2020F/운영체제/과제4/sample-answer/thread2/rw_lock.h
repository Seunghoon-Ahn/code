#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct rw_lock
{
	int nReadCnt;		// 읽기 Thraed count
	int nWriteCnt;		// 쓰기 Thread count
	int nWritePresent;	// 쓰기 상태 화성화 여부
	int rStart;
	pthread_mutex_t mtx;		// mutex 객체
	pthread_cond_t 	cndRead;	// 읽기 조건 객체
	pthread_cond_t	cndWrite;	// 쓰기 조건 객체
};

void init_rwlock(struct rw_lock * rw);
void r_lock(struct rw_lock * rw);
void r_unlock(struct rw_lock * rw);
void w_lock(struct rw_lock * rw);
void w_unlock(struct rw_lock * rw);
long *max_element(long* start, long* end);
long *min_element(long* start, long* end);
