#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE (256UL * 1024 * 1024) // 256 MB
#define PAGE 4096

void wait_step(const char *msg){
    printf("\n--- %s ---\n", msg);
    printf("grep -E 'VmSize|VmRSS' /proc/%d/status\n", getpid());
    printf("press ENTER, to continue...");
    getchar();
}

int main(void){
	putchar('\n');
	printf("Program started. PID: %d\n", getpid());
    	wait_step("Before allocation");

    	char *ptr = (char*)malloc(SIZE);
    	if (!ptr){
        	perror("malloc failed");
        	return 1;
    	}

    	wait_step("After malloc (Lazy Allocation)");

    	printf("touching pages...\n");
    	for (size_t i = 0; i < SIZE; i += PAGE) {
        	ptr[i] = 1;
    	}

    	wait_step("After allocation (Physical Allocation)");

    	free(ptr);

	putchar('\n');
	return 0;
}
