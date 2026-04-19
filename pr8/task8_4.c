#include <stdio.h>
#include <unistd.h>

int main(void){
	putchar('\n');

	int pid;
	pid = fork();
	printf("%d\n", pid);

	putchar('\n');
	return 0;
}
