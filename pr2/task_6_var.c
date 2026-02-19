#include <stdio.h>
#include <stdlib.h>


void find_min_recursive_stack(int i){

	if((i % 10000) == 0){
		printf("current depth: %d\n", i);
	}
	find_min_recursive_stack(i + 1);
}

int main(void){
	putchar('\n');
	printf("%s\n", "Let`s test deep recursion");

	find_min_recursive_stack(1);

	putchar('\n');
	return 0;
}
