#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct iL{
	int val;
	struct iL* next;
} intList;

intList *init_intList(int key)
{
	intList *result = malloc(sizeof(intList));
	result->val = key;
	result->next = NULL;

	return result;
}

intList *append_intList(intList *root, int key)
{
	intList *new_root = malloc(sizeof(intList));
	new_root->val = key;
	new_root->next = root;

	return new_root;
}

intList *insertSorted_intList(intList *root, int key)
{

	intList *new = malloc(sizeof(intList));
	new->val = key;
	new->next = NULL;

	if(root == NULL) return new;

	if(root->val >= key)
	{
		new->next = root;
		return new;
	}

	intList *it;
	intList *temp;
	for(it = root; it->next != NULL && it->next->val < key; it = it->next);

	temp = it->next;
	it->next = new;
	new->next = temp;

	return root;
	
}

int isContained_intList(intList *root, int key)
{
	intList *it = root;
	while(it != NULL)
	{
		if(it->val == key) return 1;
		it = it->next;
	}

	return 0;

}

void destroy_intList(intList *root)
{
	intList *it = root;
	intList *temp;
	while(it != NULL)
	{
		temp = it->next;
		free(it);
		it = temp;
	}
}

void output_intList(intList *root)
{
	intList *it = root;
	printf("Output Liste: ");
	while(it != NULL)
	{
		printf("%i -> ", it->val);
		it = it->next;
	}
	printf("NULL\n");
}

int main(int args, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int i;
	intList *list = NULL;

	if(args < 3) return EXIT_FAILURE;
	FILE *src = fopen(argv[1],"r");
	FILE *dest = fopen(argv[2], "w+");
	while((read = getline(&line, &len, src)) != -1)
	{
		i = atoi(line);
		printf("%i gelesen.\n", i);
		if(!isContained_intList(list, i))
		{
			printf("%i hinzugefügt.\n", i);
			list = insertSorted_intList(list, i);
			fprintf(dest, "%i\n", i);

			free(line);
			line = NULL;
		} else{
			printf("%i wird nicht hinzugefügt (bereits vorhanden).\n", i);
		}
	}
	output_intList(list);
	destroy_intList(list);
	fclose(dest);
	fclose(src);

	return 0;
}
