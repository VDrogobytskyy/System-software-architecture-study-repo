#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	putchar('\n');

	if(argc < 2){
		fprintf(stderr, "Program requires more files!");
		return EXIT_FAILURE;
	}

	char text_buffer[1000];
	int lines = 0;

	for(int i = 1; i < argc; i++){
		FILE *file = fopen(argv[i], "r");

		if(file == NULL){
			perror(argv[1]);
			continue;
		}

		while(fgets(text_buffer, 1000, file)){
			printf("%s", text_buffer);
			lines++;


			if(lines == 20){
				printf("%s", "--More--");
				getchar();
				lines = 0;
			}
		}

		fclose(file);
	}

	putchar('\n');
	return 0;
}
