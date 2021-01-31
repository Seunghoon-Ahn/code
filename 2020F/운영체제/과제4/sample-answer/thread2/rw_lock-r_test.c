#include "rwlock.h"

void init_rwlock(struct rw_lock* rw)
{
	//	Write the code for initializing your read-write lock.
	// ����ü�� �ʱ�ȭ �Ѵ�.
	rw->nReadCnt = 0;
	rw->nWriteCnt = 0;
	rw->nWritePresent = 0;

	rw->rStart = 0;
	
	// cond�� mutex�� �ʱ�ȭ�Ѵ�.
	pthread_mutex_init(&rw->mtx, NULL);
	pthread_cond_init(&rw->cndRead, NULL);
	pthread_cond_init(&rw->cndWrite, NULL);
}

void r_lock(struct rw_lock* rw)
{
	//	Write the code for aquiring read-write lock by the reader.
	// �б� ���

	pthread_mutex_lock(&rw->mtx);
	rw->rStart = 1;
	
	while (rw->nWritePresent) // ���� ���� ������ ��ٴ�.
	{
		pthread_cond_wait(&rw->cndRead, &rw->mtx);
	}
	// ���� �ʴ´� (�б� �۾� ���� ����)
	rw->nReadCnt++;
	pthread_mutex_unlock(&rw->mtx);
}

void r_unlock(struct rw_lock* rw)
{
	//	Write the code for releasing read-write lock by the reader.
	// �б� ��� ����

	pthread_mutex_lock(&rw->mtx);

	rw->nReadCnt--;
	if (rw->nReadCnt == 0)
	{
		// �д� ���� ������ ���� ��� ����
		pthread_cond_broadcast(&rw->cndWrite);
	}
	pthread_mutex_unlock(&rw->mtx);
}

void w_lock(struct rw_lock* rw)
{
	//	Write the code for aquiring read-write lock by the writer.
	pthread_mutex_lock(&rw->mtx);
	// ���� ���

	while (rw->nReadCnt > 0 || rw->nWritePresent || !rw->rStart)
	{
		// �д� ���� �ְų� ���� ������ ���
		pthread_cond_wait(&rw->cndWrite, &rw->mtx );
	}

	// �д� ���� ���� ���� ���� ������ ���� ���� Ȱ��ȭ
	rw->nWritePresent = 1;
	pthread_mutex_unlock(&rw->mtx);
}

void w_unlock(struct rw_lock* rw)
{
	//	Write the code for releasing read-write lock by the writer.
	// ���� ��� ����
	pthread_mutex_lock(&rw->mtx);
	rw->nWritePresent = 0; // ���� ���¸� ��Ȱ��ȭ�ϰ�, �б�/���� ��� ����
	pthread_cond_broadcast(&rw->cndWrite);
	pthread_cond_broadcast(&rw->cndRead);
	pthread_mutex_unlock(&rw->mtx);
}
