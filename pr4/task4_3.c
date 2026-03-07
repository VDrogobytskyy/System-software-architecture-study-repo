#include <stdio.h>
#include <stdlib.h>


int main(void){
	putchar('\n');
	void *ptr = malloc(0);

	if(ptr == NULL){
		printf("%s\n", "malloc(0) returned NULL value!");
	}else{
		printf("%s\n", "malloc(0) returned NOT NULL value!");
	}
	
	free(ptr);
	putchar('\n');
	return 0;
}
