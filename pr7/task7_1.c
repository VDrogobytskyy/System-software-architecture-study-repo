#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	putchar('\n');
	FILE *pipe_in, *pipe_out;
	char buffer[1000];
	char storage[1000];

	pipe_in = popen("sudo rwho", "r");
	if(pipe_in == NULL){
		fprintf(stderr, "Error for pipe_in");
		return EXIT_FAILURE;
	}

	pipe_out = popen("more", "w");
	if(pipe_out == NULL){
		fprintf(stderr, "Error for pipe_out");
		return EXIT_FAILURE;
	}

	while(fgets(buffer, 1000, pipe_in) != NULL){
		strcat(storage, buffer);
	}

	for(int i = 0; i < 50; i++){
		fputs(storage, pipe_out);
	}

	pclose(pipe_in);
	pclose(pipe_out);

	putchar('\n');
	return 0;
}
