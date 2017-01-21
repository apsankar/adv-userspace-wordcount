#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	char *token;
	char *saveptr1;
	char buffer[100];
	if (argv[1])  fp = freopen(argv[1],"r",stdin);
	if (!fp) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	while(fgets(buffer,sizeof(buffer),stdin) != NULL) {
		token = strtok_r(buffer,"\n", &saveptr1);
		printf("(%s,1)\n",token);
	} 
	exit(EXIT_SUCCESS);
}