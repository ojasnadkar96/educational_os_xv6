#include "types.h"
#include "stat.h"
#include "user.h"
#include "locks.h"

//xchg function taken from x86.h
uint
xchg1(volatile uint *addr, uint newval)
{
  uint result;

  // The + in "+m" denotes a read-modify-write operand.
  asm volatile("lock; xchgl %0, %1" :
               "+m" (*addr), "=a" (result) :
               "1" (newval) :
               "cc");
  return result;
}

void
thread_spin_init(struct thread_spinlock *lk)
{
 lk->locked = 0; //initializing the locked attribute
}

void
thread_spin_lock(struct thread_spinlock *lk)
{
 while(xchg1(&lk->locked,1)!=0); //atomic function
 //lock is acquired
 __sync_synchronize();
}

void
thread_spin_unlock(struct thread_spinlock *lk)
{
 if(!lk->locked)
  {
     return;
  } 
 __sync_synchronize();
 asm volatile("movl $0, %0" : "+m" (lk->locked) : ); //assembly function to release lock
}

void
thread_mutex_init(struct thread_mutex *m)
{
 m->locked = 0; //similar to locks
}

void
thread_mutex_lock(struct thread_mutex *m)
{
 while(xchg1(&m->locked,1)!=0); //atomic function
 //mutex acquired
 __sync_synchronize();
}

void
thread_mutex_unlock(struct thread_mutex *m)
{
 if(!m->locked)
  {
     return;
  } 
 __sync_synchronize();
 asm volatile("movl $0, %0" : "+m" (m->locked) : ); //assembly function to release mutex
}

void thread_cond_init(struct thread_cond *cv)
{
 cv->signal = 0; //initialize value of signal
}

void thread_cond_signal(struct thread_cond *cv)
{
 xchg1(&cv->signal,1);
}

void pthread_cond_wait(struct thread_cond *cv, struct thread_mutex *m)
{
 while(cv->signal == 0)
  {
   //unlocking the variable
   thread_mutex_unlock(m);
   sleep(1);
  }
 //locking the variable
 thread_mutex_lock(m);
 cv->signal = 0;
}

//fuction to return tid
int gettid(void)
{
 uint stack_p;
 uint page_size = 4096;
 stack_p = ((uint)&stack_p)/page_size; //local variable is in the stack
 stack_p = (stack_p+1)*page_size; //top of the stack
 stack_p -= sizeof(struct tls); //add tls to the top of the stack

 struct tls *t = (struct tls*)stack_p; //typecast stack_p to type tls

 if(t->tid < 0)
 {
   return -1;
 }

 return t->tid;
}
