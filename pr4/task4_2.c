#include <stdio.h>
#include <stdlib.h>


int main(void){
	putchar('\n');
	int xa = 9999999;
	int xb = 1000000000000;
	int num = xa * xb;

	printf("%s%d\n", "num after xa * xb(9999999 * 1000000000000) = ", num);
	printf("%s\n", "let`s convert this variable into size_t format!");
	
	size_t t_num = (size_t)num;
	printf("%s%zu\n", "num in size_t: ", t_num);

	void *ptr = malloc(t_num);
	if(ptr){
		printf("%s\n", "memory allocated succesfully!");
		free(ptr);
	}else{
		fprintf(stderr, "memory allocated fail");
	}

	putchar('\n');
	return 0;
}
