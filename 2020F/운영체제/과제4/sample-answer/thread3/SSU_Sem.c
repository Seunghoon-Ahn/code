#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include "SSU_Sem.h"

void SSU_Sem_init(SSU_Sem *s, int value)
{
	// semaphore�� ��ü�� �ʱ�ȭ
	pthread_mutex_init(&s->mutex_sem, NULL);
	pthread_cond_init(&s->cond_zem, NULL);
	s->cnt = value; 
}

void SSU_Sem_up(SSU_Sem *s) {

	// semaphore��ü�� count down
	pthread_mutex_lock(&(s->mutex_sem));
	s->cnt--;
	// count�� ������ ���
	if (s->cnt< 0)
		pthread_cond_wait(&(s->cond_sem), &(s->mutex_sem));

	pthread_mutex_unlock(&(s->mutex_sem));
}

void SSU_Sem_down(SSU_Sem *s) {
	// semaphore��ü�� count up
	pthread_mutex_lock(&(s->mutex_sem));
	s->cnt++;
	pthread_cond_signal(&(s->cond_sem));
	pthread_mutex_unlock(&(s->mutex_sem));
}
