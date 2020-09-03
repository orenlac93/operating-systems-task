#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<errno.h>



int main(int argc , char **argv)
{
	
	int num = 0;
	num = atoi(argv[1]);
	
	kill(num , 0);
	
	if(errno == ESRCH) 
    {
	    printf("Process %d does not exist\n" , num); 
    }
	else if(errno == EPERM)
	{
		printf("Process %d exists but we have no permission\n" , num);
	}	
	else
	{
		printf("Process %d exists\n" , num); 
	}
	
	return 0;
}	