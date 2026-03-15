#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

#define COUNT 10000
#define SIZE 128

int main(void){
	void *ptr[COUNT];

    	printf("%s\n", "Let`s check stats before program start!");
    	malloc_stats();
	putchar('\n')
;
   	for (int i = 0; i < COUNT; i++) {
        	ptr[i] = malloc(SIZE);
    	}

    	printf("%s%d%s\n", "stats after allocation: ", COUNT, "blocks!");
    	malloc_stats();
	putchar('\n');

	for (int i = 0; i < COUNT; i += 2) {
        	free(ptr[i]);
    	}

    	printf("%s\n", "stats after freeing every second block:");
	malloc_stats();
	putchar('\n');

	void *big_block = malloc(SIZE * 100);

	if(!big_block){
		fprintf(stderr, "big memory block allocation failed\n");
	}else{
		printf("%s\n", "big memory block allocation success!");
	}

    	printf("%s\n", "stats after trying of allocation big block:");
    	struct mallinfo2 mi = mallinfo2();
    	printf("free memory in fragments (fordblks): %zu bites:\n", mi.fordblks);
    	printf("memory get from system: %zu bites\n", mi.arena);

    	for (int i = 1; i < COUNT; i += 2){
		 free(ptr[i]);
	}
    	free(big_block);

    	return 0;
}
