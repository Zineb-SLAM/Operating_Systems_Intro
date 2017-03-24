#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

pid_t pid;
struct sigaction sa_child, sa_parent;
char* min_letters;
char* cap_letters;
unsigned int counter_child = 1;
unsigned int counter_parent = 1;
void init_table()
{
	char ch = 'a';
	unsigned int i = 0;
    cap_letters = malloc(sizeof(char)*26);
    min_letters = malloc(sizeof(char)*26);

    while(ch<='z')
    {
        min_letters[i] = ch;
        ch++;
        ++i;
    }

    ch = 'A';
    i = 0;
    while(ch<='Z')
    {
        cap_letters[i] = ch;
        ch++;
        ++i;
    }
    return;
}

void child_handler()
{
	
	unsigned int i = 0;
	//printf("in child \n");
	while(i < counter_child)
	{
		printf("%c ",*min_letters);
		fflush(stdout);
		min_letters++;
		i++;
		sleep(1);
	}	
	counter_child++;
	kill(getppid(), SIGUSR1);
}


void parent_handler()
{
	unsigned int i = 0;
	while(i < counter_parent)
	{
		printf("%c ",*cap_letters);
		fflush(stdout);
		if((*cap_letters) == 'Z')
			exit(2);

		sleep(1);
		cap_letters++;
		i++;
	}
	counter_parent++;
	kill(pid, SIGUSR1);
}

int main()
{
	printf("Hello \n");
	init_table();
    
	pid = fork();

	if(pid == -1)
	{
		printf("fork() Failed \n");
		return 1;
	}

	if(pid == 0)//Child
	{
		sa_child.sa_handler = child_handler;
		sigaction(SIGUSR1, &sa_child, NULL);
		while(1)
		{
			pause();
		}

	}
	else //Parent
	{
		sa_parent.sa_handler = parent_handler;
		sigaction(SIGUSR1, &sa_parent, NULL);
		sleep(1);

		kill(pid, SIGUSR1);
		while(1)
		{
			pause();
		}
	}	

	free(min_letters);
	free(cap_letters);	

	return 0;
}

//aAbcBCdefDEFghijGHIJklmnoKLMNOpqrstuPQRSTUvwxyzVWXYZ