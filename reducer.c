#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
	char *name;
	int count;
	struct Word *next;
} Word;

//adding new nodes: the head of the list, and the string to be
//searched are passed as parameters. We iterate through
//the list, comparing each struct with the string. On a 
//match, we set a flag and break. If the flag is unset,
//it means we did not find a match. Head->next points to NULL.
//at the current head, we copy the string and init count to 1.

int main () {
	char *str1, *token, *saveptr;
	char buffer[100];
	Word *root;
	root = NULL;

	while (fgets(buffer,sizeof(buffer),stdin) != NULL) {
		Word *head = root;
		token = strtok_r(buffer,"\n", &saveptr);
		str1 = strtok_r(token,"(",&saveptr);
		str1 = strtok_r(str1,",",&saveptr);

		if (head == NULL) {
			head = malloc(sizeof(Word));
			head->name = strdup(str1);
			head->count = 1;
			head->next = NULL;
			root = head;
		}
		//do the first characters match?
		else if (strncmp(head->name,str1,1) == 0) {
			int flag=0;
			if (strncmp(head->name,str1,100) == 0) {
				(head->count)++;
				flag=1;
			}
			else {
				while (head->next != NULL) {
					head = head->next;
					if (strncmp(head->name,str1,100) == 0) {
						(head->count)++;
						flag =1;
					}
				}
			}

			if (flag == 0) {
				Word *temp = malloc(sizeof(Word));
				temp->name = strdup(str1);
				temp->count=1;
				temp->next = NULL;
				head->next = temp;
			}
		}

		else { //print out the contents
			printf("(%s,%d)\n",head->name,head->count);
			while (head->next != NULL) {
		    head = head->next;
			printf("(%s,%d)\n",head->name,head->count);
			}
			//deleting the list:
			Word *temp;
			while (root != NULL) {
			temp = root;
			root = root->next;
			free(temp);
			}
			//starting over with new alphabet:
			root = malloc(sizeof(Word));
			root->name = strdup(str1);
			root->count = 1;
			root->next = NULL;
		}
	}
	Word *head = root;
	if (head != NULL) { //print out the contents AFTER EOF:
		printf("(%s,%d)\n",head->name,head->count);
		while (head->next != NULL) {
 			head = head->next;
			printf("(%s,%d)\n",head->name,head->count);
			}
		}
	//deleting the list:
	Word *temp;
	while (root != NULL) {
	temp = root;
	root = root->next;
	free(temp);
	}

	exit(EXIT_SUCCESS);
}

