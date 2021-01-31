#include <pthread.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct zemaphore {
	int cnt;		// count
	pthread_mutex_t mutex_sem;	// mutex 
	pthread_cond_t cond_sem;	// cond 
}SSU_Sem;

void SSU_Sem_init(SSU_Sem *, int);
void SSU_Sem_up(SSU_Sem *);
void SSU_Sem_down(SSU_Sem *);