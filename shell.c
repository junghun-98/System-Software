#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_LINE 1024

void run_shell(char * cmd){
	char * str = cmd;
	int size = strlen(str);
	char blank[] = " ";
	
	char * token = strtok(str, blank);

	char * argv[3];
	int i = 0;
	while(token != NULL){
		argv[i] = token;
		i++;
		token = strtok(NULL, blank);
	}
	
	argv[i] = NULL;
	
	pid_t pid;

	if((pid = fork()) == 0){
		if(execvp(argv[0], argv) < 0){
			perror("Invalid Command!\n");
			exit(0);
		}
	}
	else{
		if(waitpid(pid, NULL, 0) < 0){
			perror("Some Problem Program!\n");
			exit(0);
		}
	}
	printf("\n");
}

int main(){
	char comand[MAX_LINE];
	char username[MAX_LINE];

	printf("Eter your name : ");
	scanf("%s", username);
	
	while(1){
		char cwd[MAX_LINE];
	       	getcwd(cwd, sizeof(cwd));
		
		printf("%s %s$ > ", username, cwd);
		
		scanf(" %[^\n]s", comand);
		
		printf("\n");
		run_shell(comand);
	}
}
