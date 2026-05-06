#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    putchar('\n');

    int n = 5;
    pid_t pid;

    for (int i = 1; i <= n; i++) {
        pid = fork();

        if (pid < 0) {

            perror("fork failed");
            exit(1);
        } 
        else if (pid == 0) {

            printf("Fork process №%d (PID: %d)\n", i, getpid());
            exit(0);
        }

    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("All PIDs finished, program finished.\n");

    putchar('\n');
    return 0;
}
