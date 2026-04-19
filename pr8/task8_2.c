#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void){
    putchar('\n');

    int fd;
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];

    fd = open("testfile.bin", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1){
        perror("Error file openning");
        return 1;
    }

    write(fd, data, sizeof(data));

    lseek(fd, 3, SEEK_SET);

    ssize_t bytes_read = read(fd, buffer, 4);

    printf("Bites red: %zd\n", bytes_read);
    printf("What we have in buffer: ");

    for (int i = 0; i < bytes_read; i++){
        printf("%d ", buffer[i]);
    }
    putchar('\n');

    close(fd);
    unlink("testfile.bin");

    putchar('\n');
    return 0;
}
