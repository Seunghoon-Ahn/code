#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include "SSU_Sem.h"

void SSU_Sem_init(SSU_Sem *s, int value) {
  pthread_mutex_init(&s->mutex, NULL);
  pthread_cond_init(&s->cond, NULL);
  s->pr = value;
}

void SSU_Sem_down(SSU_Sem *s) {
	pthread_mutex_lock(&s->mutex);
	while(s->pr == 0)
		pthread_cond_wait(&s->cond, &s->mutex);
	++(s->pr);
	pthread_mutex_unlock(&s->mutex);
}

void SSU_Sem_up(SSU_Sem *s) {
	pthread_mutex_lock(&s->mutex);
	--(s->pr);
	pthread_mutex_unlock(&s->mutex);
	pthread_cond_signal(&s->cond);
}
