#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
	int n = 11;
	int *ptr = (int*)malloc(n*sizeof(int));
	char name[22];
	scanf("%21s", name);
	//if(strlen(name) > 20) ERR("Name too long\n");
	printf("Hello %s\n", name);
	/*
	ptr[0] = 1;
	for(int i=1; i<n; i++){
		ptr[i] = ptr[i-1]*2;
		printf("%d ", ptr[i]);
	}
	printf("Hello World. Ngnl It's nice to be back\n");
	*/
	return EXIT_SUCCESS;
}
