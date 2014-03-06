#include "threadpool.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct task{
    void (*routine)(void*);
    void * arg;
    struct task * next;
}Task;

struct threadpool{
    int num_threads;
    pthread_t * threads;
    Task * queueHead;
    Task * queueTail;
    int queueSize;
    pthread_mutex_t queueLock;
    pthread_cond_t queueNotify;
};
void * work(void * p){
    
    Threadpool * pool = (Threadpool *)p;
    Task * t;
    
    while(1){
        pthread_mutex_lock(&(pool->queueLock));
        
		while(pool->queueSize == 0) {
            pthread_cond_wait(&(pool->queueNotify), &(pool->queueLock));
        }
        
        t = pool->queueHead;	//get the head of the queue
        pool->queueSize--;		//decriment the size.
        
        /*update head/tail pointers*/
        if(pool->queueSize == 0){
			pool->queueHead = NULL;
			pool->queueTail = NULL;
		}
		else{
			pool->queueHead = t->next;
		}
        

		pthread_mutex_unlock(&(pool->queueLock));
		(t->routine) (t->arg);   //actually do work.
        
        printf("removed task from pool\n");
		free(t);

    }
    
    
}

Threadpool * createPool(int threads){
    Threadpool * pool;
    
    if((pool = (Threadpool*)malloc(sizeof(Threadpool))) == NULL)
        return NULL;
    
    if((pool->threads = (pthread_t *)malloc(sizeof(pthread_t)*threads)) == NULL)
        return NULL;
    
    
    /*initialise the queue structure*/
    pool->num_threads = threads;
    pool->queueHead = NULL;
    pool->queueTail = NULL;
    
    //initialize mutex and condition variables.
    if(pthread_mutex_init(&pool->queueLock,NULL) || pthread_cond_init(&(pool->queueNotify),NULL))
        return NULL;

    int i;
    for (i = 0;i < pool->num_threads;i++) {
        if(pthread_create(&(pool->threads[i]),NULL,work,pool)) {
            return NULL;
        }
    }
    /*we got this far, we must have done everything right...*/
    printf("created Threadpool\n");
    return pool;
}

void addTaskToPool(Threadpool * pool, void (*routine)(void*), void *arg) {
    
    printf("added task to pool\n");
    
    if(routine == NULL || pool == NULL)
        return;
    Task * t;
    t = (Task*) malloc(sizeof(Task));
    
    t->routine = routine;
	t->arg = arg;
	t->next = NULL;
    
    pthread_mutex_lock(&(pool->queueLock));
    
    if(pool->queueSize == 0){
		pool->queueHead = t;  //set to only one
		pool->queueTail = t;
		pthread_cond_signal(&(pool->queueNotify));  //I am not empty.
	}
    else{
		pool->queueTail->next = t;	//add to end;
		pool->queueTail = t;
	}
	pool->queueSize++;
	pthread_mutex_unlock(&(pool->queueLock));  //unlock the queue.

}
void destroy(Threadpool * pool){
  
     while(pool->queueSize != 0) {
     }

     //kill everything.
    int i=0;
     for(i=0;i < pool->num_threads;i++) {
         pthread_join(pool->threads[i],NULL);
     }

    free(pool->threads);

    pthread_mutex_destroy(&(pool->queueLock));
    pthread_cond_destroy(&(pool->queueNotify));
    
    free(pool);
    return;

}
