#include "types.h"
#include "stat.h"
#include "user.h"
#include "locks.h"

#define MAX_THREADS 5

typedef struct balance {
	char name[32];
	char amount;
} balance_t;


DEFINE_PER_THREAD(balance_t, balance); //using cute macros defined in locks.h

int i;

volatile int total_balance = 0;

volatile unsigned int delay(unsigned int d)
{
  unsigned int i;
  for (i = 0; i < d; i++)
      {
       __asm volatile( "nop" ::: );
      }
  return i;
}

//function initializes per-thread variables using cute macros
int
foo()
{
 per_thread_balance(balance).amount += gettid(); //cute macros
 thread_exit();
 return 0;
}

//this functions does all the operations of thread_ptv.c, but it uses cute macros
int
main(int argc, char *argv[])
{
  for (i = 0; i < MAX_THREADS; i++)
     {
       balance[i].amount = 1;
       balance[i].name[0] = (char) i + 'A';
     }

  void *baseAddress = sbrk(0);

  for (i = 0; i < MAX_THREADS; i++)
      {
	void* sb = sbrk(4096);
	thread_create((void *) foo, baseAddress, sb);
      }

  for (i = 0; i < MAX_THREADS; i++)
      {
	thread_join();
      }

  for (i = 0; i < MAX_THREADS; i++)
      {
	printf(1, "  thread_number : %d\n  thread_name   : %s\n  thread_amount : %d \n  done using cute macros\n\n", i, balance[i].name
              ,balance[i].amount);
      }

	exit();
}
