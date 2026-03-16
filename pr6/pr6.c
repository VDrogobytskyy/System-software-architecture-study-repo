#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	putchar('\n');

   	int fd1 = open("test1.txt", O_RDONLY);
    	int fd2 = open("test2.txt", O_CREAT | O_WRONLY, 0644);

    	if (fd1 != -1){
		close(fd1);
	}
    	if (fd2 != -1){
		 close(fd2);
	}

	putchar('\n');
	return 0;
}
