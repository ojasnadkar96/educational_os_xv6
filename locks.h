#ifndef _LOCKS_H_
#define _LOCKS_H_

//struct for spinlocks
struct thread_spinlock
{
 uint locked;
 //we have taken this attribute from spinlock.h
};

//struct for mutex
struct thread_mutex
{
 uint locked;
 //we make a similar struct for mutex
};

//struct for conditional variables
struct thread_cond
{
 uint signal;
};

struct q
{
 struct thread_cond cv;
 struct thread_mutex m;
 void *ptr;
//shared struct for threads
};

struct tls //thread local store for per-thread variables
{
 uint tid;
};

//cute macros for per-thread variables
#define DEFINE_PER_THREAD(type, name) type name[MAX_THREADS]
#define per_thread_balance(name) name[gettid()]

//functions in locks.c
uint xchg1(volatile uint*,uint);
void thread_spin_init(struct thread_spinlock*);
void thread_spin_lock(struct thread_spinlock*);
void thread_spin_unlock(struct thread_spinlock*);
void thread_mutex_init(struct thread_mutex*);
void thread_mutex_lock(struct thread_mutex*);
void thread_mutex_unlock(struct thread_mutex*);
void thread_cond_init(struct thread_cond*);
void thread_cond_signal(struct thread_cond*);
void pthread_cond_wait(struct thread_cond*,struct thread_mutex*);
int gettid(void);

#endif
