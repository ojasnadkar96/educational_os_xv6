#include "types.h"
#include "stat.h"
#include "user.h"
#include "locks.h"

struct balance {
	char name[32];
	int amount;
};

struct thread_mutex m; //mutex to fix malloc

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

//same function as threads.c
void do_work(void *arg)
{
  int i;
  int old;

  struct balance *b = (struct balance*) arg;
  printf(1, "Starting do_work: s:%s\n", b->name);

  for (i = 0; i < b->amount; i++)
      {
	old = total_balance;
	delay(10000);
	total_balance = old + 1;
      }

  printf(1, "Done s:%s\n", b->name);
  thread_exit();
  return;
}

int main(int argc, char *argv[])
{
  thread_mutex_init(&m);

  struct balance malloc_test  = { "malloc_test", 6000 };

  int i;
  void * stack;
  
  //we try allocating memory to 5 new  threads using new_malloc()
  for (i = 0; i < 5; i++)
      {
	stack = new_malloc(4096); //new_malloc is used here (it uses mutual exclusion to make it thread safe)
	thread_create(do_work, (void*) &malloc_test, stack);
      }

  for (i = 0; i < 5; i++)
      {
	thread_join();

      }

  printf(1, "malloc() is now atomic (it can be used concurrently)\n");
  exit();
}
