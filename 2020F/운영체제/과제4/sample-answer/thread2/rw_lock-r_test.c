#include "rwlock.h"

void init_rwlock(struct rw_lock* rw)
{
	//	Write the code for initializing your read-write lock.
	// 구조체를 초기화 한다.
	rw->nReadCnt = 0;
	rw->nWriteCnt = 0;
	rw->nWritePresent = 0;

	rw->rStart = 0;
	
	// cond와 mutex를 초기화한다.
	pthread_mutex_init(&rw->mtx, NULL);
	pthread_cond_init(&rw->cndRead, NULL);
	pthread_cond_init(&rw->cndWrite, NULL);
}

void r_lock(struct rw_lock* rw)
{
	//	Write the code for aquiring read-write lock by the reader.
	// 읽기 잠금

	pthread_mutex_lock(&rw->mtx);
	rw->rStart = 1;
	
	while (rw->nWritePresent) // 현재 쓰고 있으면 잠근다.
	{
		pthread_cond_wait(&rw->cndRead, &rw->mtx);
	}
	// 쓰지 않는다 (읽기 작업 갯수 증가)
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
		// 읽는 것이 없으면 쓰기 잠금 해제
		pthread_cond_broadcast(&rw->cndWrite);
	}
	pthread_mutex_unlock(&rw->mtx);
}

void w_lock(struct rw_lock* rw)
{
	//	Write the code for aquiring read-write lock by the writer.
	pthread_mutex_lock(&rw->mtx);
	// 쓰기 잠금

	while (rw->nReadCnt > 0 || rw->nWritePresent || !rw->rStart)
	{
		// 읽는 것이 있거나 쓰고 있으면 잠금
		pthread_cond_wait(&rw->cndWrite, &rw->mtx );
	}

	// 읽는 것이 없고 쓰고 있지 않으면 쓰기 상태 활성화
	rw->nWritePresent = 1;
	pthread_mutex_unlock(&rw->mtx);
}

void w_unlock(struct rw_lock* rw)
{
	//	Write the code for releasing read-write lock by the writer.
	// 쓰기 잠금 해제
	pthread_mutex_lock(&rw->mtx);
	rw->nWritePresent = 0; // 쓰기 상태를 비활성화하고, 읽기/쓰기 잠금 해제
	pthread_cond_broadcast(&rw->cndWrite);
	pthread_cond_broadcast(&rw->cndRead);
	pthread_mutex_unlock(&rw->mtx);
}
