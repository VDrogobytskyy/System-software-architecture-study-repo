#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void slow_write(int fd, const char *str) {
    for (int i = 0; i < (int)strlen(str); i++) {
        write(fd, &str[i], 1);
        usleep(30);
    }
}

void run_test(int use_append) {
    const char *filename = "test_append.txt";
    int flags = O_WRONLY | O_CREAT | O_TRUNC;
    
    if (use_append) {
        flags |= O_APPEND;
        printf("with O_APPEND\n");
    } else {
        printf("without O_APPEND\n");
    }

    int fd = open(filename, flags, 0644);
    if (fd < 0) { perror("open"); exit(1); }

    int iterations = 5000; 

    if (fork() == 0) {
        for (int i = 0; i < iterations; i++) {
            if (!use_append) lseek(fd, 0, SEEK_END);
            slow_write(fd, "00000000\n");
        }
        close(fd);
        exit(0);
    } else {
        for (int i = 0; i < iterations; i++) {
            if (!use_append) lseek(fd, 0, SEEK_END);
            slow_write(fd, "11111111\n");
        }
        wait(NULL);
        close(fd);
    }

    struct stat st;
    stat(filename, &st);
    int line_len = strlen("00000000\n");
    int expected = iterations * line_len * 2;
    
    printf("Final file size: %lld bytes\n", (long long)st.st_size);
    printf("Expected size:   %d bytes\n", expected);

    if (st.st_size < expected) {
        printf("RESULT: DATA LOSS DETECTED! (Files overlapped)\n");
    } else {
        printf("RESULT: Size is OK, but let's check for corruption...\n");
    }

    printf("First 60 bytes of file content:\n");
    char buf[61];
    int read_fd = open(filename, O_RDONLY);
    int n = read(read_fd, buf, 60);
    buf[n] = '\0';
    printf("[%s]\n\n", buf);
    close(read_fd);
}

int main(void){
    putchar('\n');

    run_test(0);
    run_test(1);

    putchar('\n');
    return 0;
}
