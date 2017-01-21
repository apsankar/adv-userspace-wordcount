#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void run_mapper(int pipefd[], char *arg);
void run_reducer(int pipefd[]);

int main(int argc, char *argv[]) {
	int pipefd[2];
	int status;
	//pipefd[0]: read end; pipefd[1]: write end.
	pid_t pid;
	//check if mapper input file is given as argument
	if (argc != 2) {
		fprintf(stderr,"Usage: %s <i/p file for mapper>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	//check if pipe is successful
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	run_mapper(pipefd,argv[1]);
	run_reducer(pipefd);
	close(pipefd[0]); //close all pipes in parent.
	close(pipefd[1]);

	while ((pid = wait(&status)) != -1);
	exit(EXIT_SUCCESS);
}

void run_mapper(int pipefd[], char *arg) {
	pid_t pid;
	switch (pid = fork()) {
		case 0: //child
			dup2(pipefd[1],1);
			close(pipefd[0]);
			execlp("./mapper","mapper",arg,(char *)NULL);
			perror("Mapper failed!");
			exit(EXIT_FAILURE);
		case -1:
			perror("Fork!");
			exit(EXIT_FAILURE);
		default: //parent
			break;
	}
}

void run_reducer(int pipefd[]) {
	int pid;
	switch (pid = fork()) {
		case 0: //child
			dup2(pipefd[0],0);
			close(pipefd[1]);
			execlp("./reducer","reducer",(char *)NULL);
			perror("Reducer failed!");
			exit(EXIT_FAILURE);
		case -1:
			perror("Fork failed!");
			exit(EXIT_FAILURE);
		default: //parent
			break; 
	}
}

