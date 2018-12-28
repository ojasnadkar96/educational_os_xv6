README - Homework 4 CS238P Fall Quarter 2018

Part 1

example program:
(thread.c)

Functionality:
Implemented thread_create(), thread_join() and thread_exit() in (proc.c)

Command on shell:
USE COMMAND thread ON SHELL TO MAKE IT RUN
$ thread

Part 2

example programs:
(thread_spinlock.c)
(thread_mutex.c)

Functionality:
Implemented spinlock functions thread_spin_init(), thread_spin_lock() and thread_spin_unlock() in (locks.c)
Implemented mutex funtions thread_mutex_init(), thread_mutex_lock() and thread_mutex_unlock() in (locks.c)
The structs (thread_spinlock and thread_mutex) are defined in locks.h

Commands on shell:
USE COMMAND thread_spinlock ON SHELL TO MAKE SPINLOCK IMPLEMENTATION RUN
USE COMMAND thread_mutex ON SHELL TO MAKE MUTEX IMPLEMENTATION RUN

$ thread_spinlock
$ thread_mutex

Extra Credit

1) Conditional Variables (15%)

example program:
(thread_cv.c)

Functionality:
Implemented the functions thread_cond_init(), thread_cond_signal() and pthread_cond_wait() in (locks.c)
Created a struct (thread_cond) in locks.h 
The example program makes use of send and recv funtions given to send and receive data between two threads using conditional variables
We send data of type int (92697 UC Irvine Zipcode) to check whether the functions are working properly

Command on shell:
USE COMMAND thread_cv ON SHELL TO MAKE CONDITIONAL VARIABLES IMPLEMENTATION RUN

$ thread_cv

2) Fix malloc() and sbrk() (10%)

example programs:
(fix_malloc.c)
(fix_sbrk.c)

Functionality:
Added new functions - new_malloc() and new_free() in umalloc.c with mutexes to fix malloc() and free() so that they can run concurrently
Used this new_malloc() function in the example file mentioned above
Added a lock (ptable.lock) to growproc() in (proc.c) so that the threads can implement sbrk() concurrently
Made sure that the thread does not deallocate complete page table in growproc()

In the examples we create 5 threads and give them a stack using malloc/sbrk, if all the threads can do_work() properly, new functions work

Command on shell:
USE COMMAND fix_malloc ON SHELL TO MAKE NEW MALLOC IMPLEMENTATION RUN
USE COMMAND fix_sbrk ON SHELL TO MAKE NEW SBRK IMPLEMENTATION RUN

$ fix_malloc
$ fix_sbrk

NOTE: I was getting an error ([fs.img] Error 1) 
      I realized that it was beacuse of this line in (mkfs.c) - fbn < (12 + (512 / sizeof(uint)))
      my _usertests file in Makefile is greater than 70KB in size (therefore the problem)
      I have therefore removed _usertests from UPROGS in Makefile

3) per-thread variables (10%)

example program:
(thread_ptv.c) 

Functionality:
Added a new structure (struct tls) which has the thread id (tid) to locks.h
Made a new function (gettid()) to return the tid value
We add the struct tid to the top of the stack and typecast it to struct tls
We create 5 threads and give different values to their per-thread variables, we then print it to see if it works properly

Command on shell:
USE COMMAND thread_ptv ON SHELL TO MAKE PER-THREAD VARIABLES IMPLEMENTATION RUN

$ thread_ptv

4) Cute Macros (10%)

exapmle program:
(cute_macros.c)

Functionality:
We add two macros DEFINE_PER_THREAD(type, name) and per_thread(name) in (locks.h)
We use same implementation as per-thread variables
In the output the line 'done using cute macros'

Command on shell:
USE COMMAND cute_macros ON SHELL TO MAKE CUTE MACROS FOR PER-THREAD VARIABLES IMPLEMENTATION RUN

$ cute_macros
 
