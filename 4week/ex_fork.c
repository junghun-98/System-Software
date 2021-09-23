#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	printf("pid : %u, ppid : %u\n", getpid(), getppid());

	pid_t cpid = fork();

	if(cpid == -1){
		perror("fork() error!");
		return 1;
	}

	if(cpid > 0){
		printf("<parent> fork return value : %u\n", cpid);
		printf("<parent> pid : %u, ppid : %u\n", getpid(), getppid());
		sleep(1);
	}
	else{
		printf("<child> fork return value : %u\n", cpid);
		printf("<child> pid : %u, ppid : %u\n", getpid(), getppid());
	}
	return 0;
}
