#include <stdio.h>
#include <stdlib.h>



int main(void){
	putchar('\n');

	void *ptr = malloc(sizeof(double));

	if(ptr){
		printf("%s%p\n", "memory for void pointer succesfully allocated! ptr adress = ", ptr);
	}else{
		fprintf(stderr, "memory allocation failed!\n");
	}

	void *reallocate_ptr = realloc(ptr, 1024 * 1024 * 1024 * 1024);

	if(!reallocate_ptr){
		fprintf(stderr, "realloc fail!\n");
		if(((char*)ptr)[0] = 'c'){
			printf("%s\n", "we still can use ptr!");
		}else{
			fprintf(stderr, "we cant access ptr anymore!\n");
		}
	}else{
		printf("%s\n", "realloc into 1024 * 1024 * 1024 * 1024 confirmed!");
	}

	
	printf("%s\n", "program didn`t finished!");
	free(reallocate_ptr);
	putchar('\n');
	return 0;
}
