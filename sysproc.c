#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "uproc.h"

int
getprocinfo(int,struct uproc*);
 
int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;
  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//system call to print backtrace of a program
int
sys_backtrace(void)
{
  return backtrace();
}

//system call to get information of all processes
int
sys_getprocinfo(void)
{
  int proc_num;
  struct uproc *myProc;
  if((argint(0,&proc_num)<0) || argptr(1,(void*)&myProc, sizeof(struct uproc))<0)
    {
      return -1;
    }  
  return getprocinfo(proc_num,myProc);
}

//system call to create a thread
int
sys_thread_create(void)
{
 int fcn;
 int arg;
 char* stack;

 if(argint(0,&fcn)<0 || fcn<0 || fcn>=myproc()->sz || argint(1,&arg)<0 || arg<0 || arg>=myproc()->sz || argptr(2,&stack,PGSIZE)<0)
   {
    return -1;
   }
 return thread_create((void(*)(void*))fcn,(void*)arg,stack); 
}

//system call which waits for all threads to execute
int
sys_thread_join(void)
{
 return thread_join();
}

//system call to exit a thread
int
sys_thread_exit(void)
{
 thread_exit();
 return 0;
}  
