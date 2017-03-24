#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

pid_t pid;
struct sigaction sa_child, sa_parent;


void measure_temp()
{
	printf("Temperature: %d C\n",(rand()%30 + 10));
}

void parent_handler()
{
	kill(pid, SIGUSR1);//sends signal to child
	alarm(5);
}

int main()
{

	printf("Hello \n");
	
	pid = fork();

	if(pid == -1)
	{
		printf("fork() Failed \n");
		return 1;
	}
	if(pid == 0)//Child
	{
		sa_child.sa_handler = measure_temp;
		sigaction(SIGUSR1, &sa_child, NULL);
		while(1)
		{
			pause();
		}

	}
	else //Parent
	{
		sa_parent.sa_handler = parent_handler;
		sigaction(SIGALRM, &sa_parent, NULL);
		alarm(5); 
		while(1)// sends a signal to himself	
		{
			sleep(1);
			printf("-ç");
			fflush(stdout);
		}
		
		//wait(NULL);
	}

	return 0;

}