#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	putchar('\n');

	if(argc != 3){
		fprintf(stderr, "Program require 3 parametrs");
		return EXIT_FAILURE;
	}

	char word_to_find[128];
	strcpy(word_to_find, argv[1]);
	char *file_name = argv[2];

	FILE *file = fopen(file_name, "r");

	if(file == NULL){
		fprintf(stderr, "Error of opening file.");
		return EXIT_FAILURE;
	}

	char text[1024];

	while(fgets(text, 1024, file) != NULL){

		if(strstr(text, word_to_find) != NULL){
			printf("%s", text);
		}
	}
	fclose(file);
	putchar('\n');
	return 0;
}
