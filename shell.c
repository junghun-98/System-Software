#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_LINE 1024

void signal_handler(int signo){
	if(signo == SIGINT){
		printf("종료를 원하시면 exit를 입력하세요.\n");
	}
	if(signo == SIGUSR1){
		printf("Hello world!\n");
	}
}

void change_directory(char * path){
	if(chdir(path) < 0){
		perror("chenge dir error!\n");
	}
}

void run_normal_cmd(char ** strv){
	pid_t pid;

	if((pid = fork()) == 0){
		if(execvp(strv[0], strv) < 0){
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

void output_redir(char ** strv){
	int fd;
	int i;
	pid_t pid;
	char * cmdv[64];

	for(i = 0; strcmp(strv[i], ">") != 0; i++){
		cmdv[i] = strv[i];
	}

	cmdv[i] = NULL;

	fd = open(strv[i + 1], O_RDWR | O_CREAT, 0644);

	if(fd < 0){
		perror("opne()");
		exit(-1);
	}
	
	if((pid = fork()) == 0){
		dup2(fd, 1);
		run_normal_cmd(cmdv);
		close(fd);
		exit(0);	
	}
	
	else{
		if(waitpid(pid, NULL, 0) < 0){
			perror("Some Problem Program\n");
			exit(0);
		}
	}
}

void run_shell(char * cmd){
	char * str = cmd;
	int size = strlen(str);
	char blank[] = " ";
	char * token = strtok(str, blank);
	char * argv[64];

	int i = 0;
	while(token != NULL){
		argv[i] = token;
		i++;
		token = strtok(NULL, blank);
	}
	
	argv[i] = NULL;
	
	//cd 명령
	if(strcmp("cd", argv[0]) == 0){
		change_directory(argv[1]);
		return;
	}
	
	//리다이렉션
	for(int j = 0; argv[j] != NULL; j++){
		if(strcmp(argv[j], ">") == 0){
			output_redir(argv);
			return;
		}
	}

	//일반 명령
	run_normal_cmd(argv);
}

int main(){
	char comand[MAX_LINE];
	char username[MAX_LINE];

	printf("Eter your name : ");
	scanf("%s", username);

	signal(SIGINT, signal_handler);
	signal(SIGUSR1, signal_handler);
	
	while(1){
		char cwd[MAX_LINE];
	       	if(getcwd(cwd, sizeof(cwd)) < 0){
			perror("getcwd() error!");
		}
			
		printf("%s %s$ > ", username, cwd);
		
		scanf(" %[^\n]s", comand);
		
		if(strcmp("exit", comand) == 0) break;

		printf("\n");
		run_shell(comand);
	}
}
