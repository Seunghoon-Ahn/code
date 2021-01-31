#include "rw_lock.h"

void init_rwlock(struct rw_lock * rw)
{
  //    Write the code for initializing your read-write lock.
	rw->status = 0;
	rw->Rnum = 0;
	rw->Wnum = 0;
	pthread_mutex_init(&(rw->read_mutex), NULL);
	pthread_cond_init(&(rw->read_cond), NULL);
	pthread_mutex_init(&(rw->write_mutex), NULL);
	pthread_cond_init(&rw->write_cond, NULL);
}

void r_lock(struct rw_lock * rw)
{
  //    Write the code for aquiring read-write lock by the reader.
	pthread_mutex_lock(&rw->read_mutex);
	rw->Rnum++;
	if(rw->Wnum != 0 || rw->status != 0)
	{
		pthread_cond_wait(&rw->read_cond, &rw->read_mutex);
	}
	
	rw->status = 1;
	pthread_mutex_unlock(&rw->read_mutex);
}

void r_unlock(struct rw_lock * rw)
{
  //    Write the code for releasing read-write lock by the reader.
	pthread_mutex_lock(&rw->read_mutex);
	rw->Rnum--;
	rw->status = 0;
	if(rw->Wnum > 0)
		pthread_cond_signal(&rw->write_cond);
	else
		pthread_cond_broadcast(&rw->read_cond);
	pthread_mutex_unlock(&rw->read_mutex);
}

void w_lock(struct rw_lock * rw)
{
  //    Write the code for aquiring read-write lock by the writer.
	pthread_mutex_lock(&rw->write_mutex);
	rw->Wnum++;

	if(rw->status != 0)
		pthread_cond_wait(&rw->write_cond, &rw->write_mutex);
	rw->status = -1;
	pthread_mutex_unlock(&rw->write_mutex);
}

void w_unlock(struct rw_lock * rw)
{
  //    Write the code for releasing read-write lock by the writer.
	pthread_mutex_lock(&rw->write_mutex);
	rw->Wnum--;
	rw->status = 0;
	if(rw->Wnum != 0)
		pthread_cond_signal(&rw->write_cond);
	else if(rw->Rnum > 0 && rw->Wnum == 0)
		pthread_cond_broadcast(&rw->read_cond);
	pthread_mutex_unlock(&rw->write_mutex);
}
