#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct rw_lock
{
	int nReadCnt;		// �б� Thraed count
	int nWriteCnt;		// ���� Thread count
	int nWritePresent;	// ���� ���� ȭ��ȭ ����
	int rStart;
	pthread_mutex_t mtx;		// mutex ��ü
	pthread_cond_t 	cndRead;	// �б� ���� ��ü
	pthread_cond_t	cndWrite;	// ���� ���� ��ü
};

void init_rwlock(struct rw_lock * rw);
void r_lock(struct rw_lock * rw);
void r_unlock(struct rw_lock * rw);
void w_lock(struct rw_lock * rw);
void w_unlock(struct rw_lock * rw);
long *max_element(long* start, long* end);
long *min_element(long* start, long* end);
