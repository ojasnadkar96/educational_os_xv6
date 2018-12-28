#include "types.h"
#include "stat.h"
#include "user.h"
#include "locks.h"

//sender thread
void
send(struct q *q, void *p)
{
   thread_mutex_lock(&q->m);
   while(q->ptr != 0)
      ;
   q->ptr = p;
   thread_cond_signal(&q->cv);
   thread_mutex_unlock(&q->m);
}

//recv thread
void*
recv(struct q *q) {
	void *p;

	thread_mutex_lock(&q->m);

	while ((p = q->ptr) == 0)
	pthread_cond_wait(&q->cv, &q->m);
	q->ptr = 0;

	thread_mutex_unlock(&q->m);
	return p;
}

void
sendthread(void *arg) {
	struct q* queue = (struct q*) arg; //creates a sending queue
	int data = 92697; //data is zipcode of UC Irvine
	send(queue, &data); //sending data using send()
	printf(1, "Data sent (conditional variable): %d\n", data);
	thread_exit();

}

void
recvthread(void* arg) {
	struct q* queue = (struct q*) arg;
	int data = *(int*)recv(queue); //recv data using recv()
	printf(1, "Data received (conditional variable): %d\n", data);
	thread_exit();
}

int main(int argc, char *argv[]) {

	struct q queue;

	void *stackOne = malloc(4096); //stack for sending thread
	void *stackTwo = malloc(4096); //stack for recv thread
	void *args = (void *)&queue;

	thread_create(sendthread, args, stackOne); //create thread to send data
	thread_create(recvthread, args, stackTwo); //create thread to recv data

	thread_join();
	thread_join(); //wait for both threads to finish

	printf(1,"We have successfully sent and recieved data using conditional variables\n");	

	exit();
	return 0;
}
