#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(void){
    putchar('\n');

    int pipefd[2];


    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

    size_t nbytes = 100 * 1024 * 1024; 
    char *buffer = malloc(nbytes);
    
    printf("Trieng to write: %zu bites\n", nbytes);

    ssize_t count = write(pipefd[1], buffer, nbytes);

    if (count == -1) {
        perror("write ERROR");
    } else {
        printf("Have wrote:  %zd bites\n", count);
        if (count < nbytes) {
            printf("Result: (Partial write)\n");
        }
    }

    free(buffer);
    close(pipefd[0]);
    close(pipefd[1]);

    putchar('\n');
    return 0;
}
