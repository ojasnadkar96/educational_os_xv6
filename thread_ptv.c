#include "types.h"
#include "stat.h"
#include "user.h"
#include "locks.h"

#define MAX_THREADS 5 //maximum number of threads for per-thread variables

int i; //loop variable

//struct balance for per-thread variables
typedef struct balance
{
  char name[32];
  char amount;
} balance_t;

//per-thread variable of type balance_t
balance_t per_thread_balance[MAX_THREADS];

//mutex for synchronization 
struct thread_mutex m;

volatile int total_balance = 0;

volatile unsigned int delay(unsigned int d) {
	unsigned int i;
	for (i = 0; i < d; i++) {
		__asm volatile( "nop" ::: );
	}
	return i;
}

//this function increments the amount(balance) of a thread by its tid value
int
foo()
{
  int tid = gettid();
  thread_mutex_lock(&m);
  per_thread_balance[tid].amount += tid;
  thread_mutex_unlock(&m);
  thread_exit();
  return 0;
}

int
main(int argc, char *argv[])
{
  //initializes per-thread variables for 5 threads
  for (i = 0; i < MAX_THREADS; i++)
       {
	per_thread_balance[i].amount = 1;
	per_thread_balance[i].name[0] = (char) i + 'A';
       }

  thread_mutex_init(&m);
  void *baseAddress = sbrk(0);
 
  //page alloction and thread creation using sbrk (for page alignment)
  for (i = 0; i < MAX_THREADS; i++)
       {
	void* sb = sbrk(4096);
	thread_create((void *) foo, baseAddress, sb);
       }

  //waiting for threads to complete
  for (i = 0; i < MAX_THREADS; i++) 
       {
	thread_join();
       }

  //printing the per-thread variables
  for (i = 0; i < MAX_THREADS; i++)
       {
	printf(1, "  thread_number : %d\n  thread_name   : %s\n  thread_amount : %d \n\n", i, per_thread_balance[i].name,
	per_thread_balance[i].amount);
       }

  exit();
}
