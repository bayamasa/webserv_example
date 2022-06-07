#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	int status;
	
	if(!(pid=fork()))
	{
		exit(1000000);
	}
	waitpid(pid,&status,0);
	printf("%d", status);
	if (WIFEXITED(status)) {
		printf("%d", WEXITSTATUS(status));
	}
}
