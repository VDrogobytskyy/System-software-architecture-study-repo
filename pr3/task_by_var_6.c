#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

int main(void){
        putchar('\n');

        size_t large_storage = 5 * 1024 * 1024; // 5 Mb
        void *ptr = malloc(large_storage);

        if(!ptr){
                fprintf(stderr, "Oops memory allocation error!\n");
                exit(0);
        }

        printf("%s\n", "We succesfully allocated 5 Mb of memory!");

        if(mlock(ptr, large_storage) == 0){
                printf("%s\n", "Everything worked, we locked memory in RAM, and it will never be placed in SWAP(HD)");
        }else{
                fprintf(stderr, "\nSomething went wrong :\\ Error: %s\n", strerror(errno));
        }

        free(ptr);

        putchar('\n');
        return 0;
}
