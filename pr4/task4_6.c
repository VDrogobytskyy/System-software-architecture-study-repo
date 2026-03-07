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

	void *real_mal_ptr = realloc(NULL, 16);
	if(!real_mal_ptr){
		fprintf(stderr, "failed to allocate memory by realloc(NULL)\n");
	}else{
		printf("%s%p\n", "confirmed allocation by realloc(NUll) real_mal_ptr = ", real_mal_ptr);
	}
	void *reallocate_ptr = realloc(ptr, 0);
	if(reallocate_ptr == NULL){
		printf("%s%p\n", "after realloc(..., 0) we have ptr = ", ptr);
		printf("%s\n", "but this memory is already free, so we cannot use it");
	}else{
		printf("%s%p\n", "realloc into 0 confirmed! ", ptr);
	}

	printf("%s\n", "program didn`t finished!");
	//this free will go like free(NULL);
	free(reallocate_ptr);
	putchar('\n');
	return 0;
}
