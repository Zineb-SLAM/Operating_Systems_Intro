#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
unsigned int nbpere,nbfils;
struct sigaction sa_child, sa_parent;
pid_t pid1, pid2;
pid_t lespid[3];
void handler_parent()
{
	nbpere++;
	printf("Le pere a recu le signal N %d", nbpere);
	if(nbpere == 3)
	{
		printf("3 signaux recus --> Desctruction \n");
		detruitrec();
		exit(0);
	}
}


void fonc_parent()
{	
	sa_parent.sa_handler = handler_parent;
	sigaction(SIGINT, &sa_parent, NULL);
	while(1)
	{
		unsigned int n = sleep(10);
		printf("Remaining time : %d \n",n);
	}

}


void handler_child()
{
	nbfils++;
	rectvert(2);

	if(nbfils == 3)
	{
		printf("3 signaux recus --> Desctruction\n");
		detruitrec();
		exit(0);
	}
}

void fonc_child()
{
	int i = 0;
	initrec();
	sa_child.sa_handler = handler_child;
	sigaction(SIGINT, &sa_child, NULL);

	while(i != -1)
	{
		i = attendreclic();
		if(i == 0)
		{
			printf("Sending message to parent \n");
			kill(getppid(), SIGINT);
		}
	}

		

}
int main()
{
	lespid[0] = getpid();
	pid1 = fork();
	lespid[1] = pid1;
	if(pid == -1)
	{
		printf("fork() Failed \n");
		return 1;
	}

	if(pid == 0)//Child
	{
		fonc_child();
		break;
		pid2 = fork();
		lespid[2] = pid2;

		if(pid == -1)
		{
			printf("fork() Failed \n");
			return 1;
		}
		else if (pid2 ==0)
		{

		}

	}
	else
	{
		fonc_parent();
	}
	return 0;
}