#include <stdio.h>
#include <stdlib.h>



int main(void){
	putchar('\n');
	void *ptr = NULL;
	int counter = 0;
	while (counter != 3) {
    		if (!ptr){
        		ptr = malloc(sizeof(int));
    			printf("%s%d%s%zu\n", "On interation: ", counter + 1, " we managed to malloc: ", sizeof(int));
		}
		counter++;
		ptr = NULL;
		free(ptr);
	}


	putchar('\n');
	return 0;
}
