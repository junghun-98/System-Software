#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid = 0;
	int status = 0;

	pid = fork();
	if(pid == -1){
		perror("fork() error!");
		exit(-1);
	}
	else if(pid == 0){
		printf("I'm child : %d\n", getpid());
		exit(1);
	}
	else{
		wait(&status);
		if((status == 0) || (status > 255)){
			printf("Child is exited with : %d\n", status << 8);
		}
		else{
			printf("Child is terminated with : %d\n", status);
		}
	}

	return 0;
}

