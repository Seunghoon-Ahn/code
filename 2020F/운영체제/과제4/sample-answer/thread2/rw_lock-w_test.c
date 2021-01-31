#include "rwlock.h"

void init_rwlock(struct rw_lock* rw)
{
	//	Write the code for initializing your read-write lock.
	// 구조체를 초기화 한다.
	rw->nReadCnt = 0;
	rw->nWriteCnt = 0;
	rw->nWritePresent = 0;
	pthread_mutex_init(&rw->mtx, NULL);
	pthread_cond_init(&rw->cndRead, NULL);
	pthread_cond_init(&rw->cndWrite, NULL);
}

void r_lock(struct rw_lock* rw)
{
	//	Write the code for aquiring read-write lock by the reader.
	// 읽기 잠금

	pthread_mutex_lock(&rw->mtx);
	while (rw->nWritePresent || rw->nWriteCnt > 0) // 쓰고있거나 쓰는 갯수가 있으면 잠금
	{
		pthread_cond_wait(&rw->cndRead, &rw->mtx);
	}
	// 쓰기 상태가 아니면 읽기 가능 -> 읽기 갯수 증가
	rw->nReadCnt++;
	pthread_mutex_unlock(&rw->mtx);
}

void r_unlock(struct rw_lock* rw)
{
	//	Write the code for releasing read-write lock by the reader.
	// 읽기 잠금 해제

	pthread_mutex_lock(&rw->mtx);
	rw->nReadCnt--;
	if (rw->nReadCnt == 0)
	{
		// 읽는 Thread가 없으면 쓰기 잠금 모두 해제
		pthread_cond_broadcast(&rw->cndWrite);
	}
	pthread_mutex_unlock(&rw->mtx);
}

void w_lock(struct rw_lock* rw)
{
	//	Write the code for aquiring read-write lock by the writer.
	// 쓰기 잠금

	pthread_mutex_lock(&rw->mtx);
	rw->nWriteCnt++; // 쓰기 thread 갯수 증가
	while (rw->nReadCnt > 0 || rw->nWritePresent) // 읽는 thread가 있거나 쓰기 상태이면 잠금
	{
		pthread_cond_wait(&rw->cndWrite, &rw->mtx);
	}
	// 사용할 수 있으면 쓰기 상태로 변경
	rw->nWriteCnt--;
	rw->nWritePresent = 1;
	pthread_mutex_unlock(&rw->mtx);
}

void w_unlock(struct rw_lock* rw)
{
	//	Write the code for releasing read-write lock by the writer.
	// 쓰기 잠금 해제

	pthread_mutex_lock(&rw->mtx);
	rw->nWritePresent = 0; // 쓰기 상태를 비활성화 하고
	// 모든 쓰레드 쓰기, 읽기 상태 가능하도록 세팅
	pthread_cond_broadcast(&rw->cndWrite);
	pthread_cond_broadcast(&rw->cndRead);
	pthread_mutex_unlock(&rw->mtx);
}
