#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int count = 0;

void sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		//printf("received SIGINT\n");	(use for debug)
		count++;
		//printf("count = %d\n" , count);	(use for debug)
	}

	else if (signo == SIGUSR1)
	{
		//printf("received SIGUSR1\n");   (use for debug)
		
		printf("recived %d (SIGINT) signals\n" , count);
	}
	else
		printf("Error\n");
}

int main(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");
    if (signal(SIGUSR1, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGUSR1\n");

  
	while(1) 
	{
		sleep(1);
	}
	return 0;
}
