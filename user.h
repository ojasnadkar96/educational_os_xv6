struct stat;
struct rtcdate;
struct uproc; //struct used to get process info
struct thread_spinlock; //struct for spinlock
struct thread_mutex; //struct for mutex
struct thread_cond; //struct for conditional variables
struct q; //shared struct
struct tls; //per-thread variables

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int backtrace(void); //call to print backtrace of a program on console
int getprocinfo(int, struct uproc*); //call to print info of all processes
int thread_create(void(*)(void*),void*,void*); //call to create a thread
int thread_join(void); //call to wait for threads to complete
int thread_exit(void); //call to exit a thread

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
void* new_malloc(uint); //fixing malloc
void new_free(void*); //fixing malloc
int atoi(const char*); 

//locks.c
uint xchg1(volatile uint*,uint);
void thread_spin_init(struct thread_spinlock*);
void thread_spin_lock(struct thread_spinlock*);
void thread_spin_unlock(struct thread_spinlock*);
void thread_mutex_init(struct thread_mutex*);
void thread_mutex_lock(struct thread_mutex*);
void thread_mutex_unlock(struct thread_mutex*);
void thread_cv_init(struct thread_cond*);
void thread_cv_signal(struct thread_cond*);
void thread_cv_wait(struct thread_cond*,struct thread_mutex*);
int gettid(void);
