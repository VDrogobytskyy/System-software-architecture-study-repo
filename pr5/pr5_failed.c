#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/resource.h>

#define COUNT 10000
#define SIZE 128

int main(void) {
    struct rlimit rl;
    rl.rlim_cur = 4 * 1024 * 1024;
    rl.rlim_max = 4 * 1024 * 1024;

    if (setrlimit(RLIMIT_AS, &rl) != 0) {
        perror("setrlimit failed");
        return 1;
    }

    void *ptr[COUNT];

    printf("%s\n", "Initial state");
    malloc_stats();

    for (int i = 0; i < COUNT; i++) {
        ptr[i] = malloc(SIZE);
        if (ptr[i] == NULL) {
            printf("%s%d\n", "Error: failed to allocate block ", i);
            break;
        }
    }

    for (int i = 0; i < COUNT; i += 2) {
        free(ptr[i]);
    }

    printf("\n%s\n", "State after creating holes (FRAGMENTATION)");
    struct mallinfo2 mi_before = mallinfo2();
    printf("%s%zu%s\n", "Total free memory (fordblks): ", mi_before.fordblks, " bytes");
    malloc_stats();

    size_t big_request = 3 * 1024 * 1024; 
    printf("\n%s%zu%s\n", "Trying to allocate contiguous block: ", big_request, " bytes...");
    
    void *big_block = malloc(big_request);

    if (big_block == NULL) {
        printf("%s\n", "!!! RESULT: malloc returned NULL (Allocation Failed) !!!");
        printf("%s%zu%s%zu%s\n", "Total free memory (", mi_before.fordblks, ") was enough for the request (", big_request, "), but it is fragmented.");
    } else {
        printf("%s\n", "Success! Allocator found or expanded memory.");
        free(big_block);
    }

    for (int i = 1; i < COUNT; i += 2) {
        if (ptr[i] != NULL) free(ptr[i]);
    }

    return 0;
}
