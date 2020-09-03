#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <linux/sched.h>
#include <sched.h>

#define gettid() syscall(__NR_gettid)

#define SCHED_DEADLINE	6

/* XXX use the proper syscall numbers */
#ifdef __x86_64__
#define __NR_sched_setattr		314
#define __NR_sched_getattr		315
#endif

#ifdef __i386__
#define __NR_sched_setattr		351
#define __NR_sched_getattr		352
#endif

#ifdef __arm__
#define __NR_sched_setattr		380
#define __NR_sched_getattr		381
#endif

static volatile int done;

struct sched_attr{
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
};

int sched_setattr(pid_t pid, const struct sched_attr *attr, unsigned int flags)
{
	return syscall(__NR_sched_setattr, pid, attr, flags);
}

int sched_getattr(pid_t pid, struct sched_attr *attr, unsigned int size, unsigned int flags)
{
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
}


int main(int argc , char **argv)
{
	
	int s_policy = 0;
	int priority = 0;
	s_policy = atoi(argv[1]);
	priority = atoi(argv[2]);
	

	int ret;
	int p;

	if(s_policy != SCHED_DEADLINE)
	{

		struct sched_param sp = { .sched_priority = priority }; // SCHED_OTHER / IDLE (only priority = 0)
		ret = sched_setscheduler(getpid(), s_policy, &sp);
		
		if(ret == -1)
		{
			perror("error");
			return 1;
		}

		/*** use for debug ***/
		//p = sched_getscheduler(getpid());
		//printf("%d\n" , p);

	}
	else
	{

		struct sched_attr sa = {
			.size = sizeof(struct sched_attr),
			.sched_policy = SCHED_DEADLINE,
			.sched_flags = SCHED_FLAG_RESET_ON_FORK,
			.sched_nice=5,
			.sched_priority=0,
			.sched_runtime=1234,
			.sched_deadline=1234,
			.sched_period=1234
		};
	
		ret = sched_setattr(getpid(), &sa, 0);
	

	
		if(ret == -1)
		{
			perror("error");
			return 1;
		}

		/*** use for debug ***/
		//p = sched_getattr(getpid(), &sa ,sizeof(struct sched_attr),0);
		//printf("%d\n" , p);

	}
	
	// sets the program runing time
	int time_to_run = 20;

	while(time_to_run > 0)
	{
		sleep(1);
		time_to_run--;
	}

	

	
	return 0;
}
