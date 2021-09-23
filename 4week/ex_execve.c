#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const * argv[]){
	pid_t pid = 0;
	int status = 0;
	char * args[] = {"ls", "-a", "-l", NULL};
	char * envp[] = {"USER=clear", "HOME=/home/clear", NULL};

	pid = fork();
	switch(pid){
		case -1:
			perror("fork() error!");
			exit(-1);
		case 0:
			execve("/bin/ls", args, envp);
			break;
	}

	if(pid > 0) { wait(&status); }

	return 0;
}

