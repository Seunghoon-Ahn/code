#include "rwlock.h"

void init_rwlock(struct rw_lock* rw)
{
	//	Write the code for initializing your read-write lock.
	// ����ü�� �ʱ�ȭ �Ѵ�.
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
	// �б� ���

	pthread_mutex_lock(&rw->mtx);
	while (rw->nWritePresent || rw->nWriteCnt > 0) // �����ְų� ���� ������ ������ ���
	{
		pthread_cond_wait(&rw->cndRead, &rw->mtx);
	}
	// ���� ���°� �ƴϸ� �б� ���� -> �б� ���� ����
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
		// �д� Thread�� ������ ���� ��� ��� ����
		pthread_cond_broadcast(&rw->cndWrite);
	}
	pthread_mutex_unlock(&rw->mtx);
}

void w_lock(struct rw_lock* rw)
{
	//	Write the code for aquiring read-write lock by the writer.
	// ���� ���

	pthread_mutex_lock(&rw->mtx);
	rw->nWriteCnt++; // ���� thread ���� ����
	while (rw->nReadCnt > 0 || rw->nWritePresent) // �д� thread�� �ְų� ���� �����̸� ���
	{
		pthread_cond_wait(&rw->cndWrite, &rw->mtx);
	}
	// ����� �� ������ ���� ���·� ����
	rw->nWriteCnt--;
	rw->nWritePresent = 1;
	pthread_mutex_unlock(&rw->mtx);
}

void w_unlock(struct rw_lock* rw)
{
	//	Write the code for releasing read-write lock by the writer.
	// ���� ��� ����

	pthread_mutex_lock(&rw->mtx);
	rw->nWritePresent = 0; // ���� ���¸� ��Ȱ��ȭ �ϰ�
	// ��� ������ ����, �б� ���� �����ϵ��� ����
	pthread_cond_broadcast(&rw->cndWrite);
	pthread_cond_broadcast(&rw->cndRead);
	pthread_mutex_unlock(&rw->mtx);
}
