#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<errno.h>


int sig = 0;
int num = 0;
int pid = 0;

int main(int argc , char **argv)
{

	pid = atoi(argv[1]);
	sig = atoi(argv[2]);
	num = atoi(argv[3]);
	
	//printf("num = %d\n" , num);	(use for debug)
	
	if(sig == 2) 
    {
		for(int i = 0; i < num; i++)
		{
			kill(pid, SIGINT);
		}
    }
	else if(sig == 10)
	{
		
		kill(pid, SIGUSR1);
	}	
	else
	{
		printf("Error\n"); 
	}
	
	return 0;
}	
